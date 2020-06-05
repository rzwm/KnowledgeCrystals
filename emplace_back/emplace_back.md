emplace_back

从C++11开始，`std::vector`新增了`emplace_back`成员函数，它与`push_back`的功能很相似，都是在`vector`的末尾添加一个新的元素。但是，`emplace_back`相比`push_back`，有两点显著的不同。

第一点，`emplace_back`的功能更加强大，它接受`vector`所存储元素的构造函数所需的参数，重点是，支持任意多个参数。

第二点，如其名`place`所示，它接受参数后，进行`in place`构造，从而节省了`push_back`所需的临时变量(如果需要的话)的构造与析构，性能得到了提升。

参考链接：[C++ difference between emplace_back and push_back function](http://candcplusplus.com/c-difference-between-emplace_back-and-push_back-function)