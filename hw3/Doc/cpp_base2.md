## cpp base
- 一些cpp基础知识点，暂时记录在此


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