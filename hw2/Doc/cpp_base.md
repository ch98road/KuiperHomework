## cpp base
- 一些cpp基础知识点，暂时记录在此


### 关键字： explicit
- https://blog.csdn.net/k6604125/article/details/126524992
- C++中的explicit关键字只能用于修饰只有一个参数的类构造函数, 它的作用是表明该构造函数是显示的, 而非隐式的, 跟它相对应的另一个关键字是implicit, 意思是隐藏的,类构造函数默认情况下即声明为implicit(隐式).

### 返回值
- 引用/指针 ： https://blog.csdn.net/qq_28256407/article/details/120185762
- 引用作为返回值就是返回变量时只返回变量地址，而指针作为返回值的作用是返回变量时必须返回地址（可被包成指针，如参考中的&temp_str）

### auto 与 auto &
- https://blog.csdn.net/artistkeepmonkey/article/details/106334555
- https://blog.csdn.net/weixin_42442319/article/details/116056114
- 不加&则永远不会被推导为引用