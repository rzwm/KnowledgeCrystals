#include <cstdio>
#include <cstring>
#include <cmath>

#pragma warning(disable : 4996)
#include "NEON_2_SSE.h"

inline float map(float v) {
	return v * v;
}

void vector_sqr(const float * __restrict src, float * __restrict dst, int len) {
	for (int i = 0; i < len; ++i) {
		dst[i] = map(src[i]);
	}
}

void vector_sqr_neon(const float * __restrict src, float * __restrict dst, int len) {
	const int end = len - len % 4;
	for (int i = 0; i < end; i += 4) {
		float32x4_t vSrc = vld1q_f32(src + i);
		float32x4_t vDst = vmulq_f32(vSrc, vSrc);
		vst1q_f32(dst + i, vDst);
	}
	
	for (int i = end; i < len; ++i) {
		dst[i] = map(src[i]);
	}
}

bool check(const float *src, int len) {
	float* dst_cpp = new float[len];
	float* dst_neon = new float[len];

	vector_sqr(src, dst_cpp, len);
	vector_sqr_neon(src, dst_neon, len);
	const bool equal = 0 == memcmp(dst_cpp, dst_neon, len * sizeof(float));

	delete[] dst_cpp;
	delete[] dst_neon;
	return equal;
}

int main() {
	const int len = 1026;
	float* src = new float[len];
	for (int i = 0; i < len; ++i) {
		src[i] = (std::rand() % 100) / 10.f;
	}

	const bool success = check(src, len);
	if (success) {
		printf("CHECK OK!\n");
	}
	else {
		printf("CHECK FAILED!\n");
	}

	delete[] src;
	return 0;
}