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


### shared_ptr的一些api
- 一个demo
```cpp
#include <iostream>
#include <memory>
using namespace ::std;

int main()
{

    shared_ptr<string> p1 = make_shared<string>("1111");
    shared_ptr<string> p2 = make_shared<string>("2222");

    swap(p1, p2);
    cout << *p1 << endl;
    cout << *p2 << endl;

    shared_ptr<string> p3(p1);
    cout << p1.use_count() << endl;
    cout << p1.unique() << endl;
    cout << p3.use_count() << endl;
    cout << p3.unique() << endl;

    // p1.reset();
    p1.reset();
    cout << p3.use_count() << endl;
    cout << p3.unique() << endl;

    unique_ptr<string> p4 = make_unique<string>("ssss");

    cout << *p4 << endl;
    // p4.reset(), p4.reset(nullptr), p4=nullptr
    p4.release();
}

```