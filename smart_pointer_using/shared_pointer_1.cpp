#include <iostream>
#include <memory>

class Widget : public std::enable_shared_from_this<Widget>{
public:
    Widget(){
        std::cout << "Widget constructor run" << std::endl;
    }
    ~Widget(){
        std::cout << "Widget destructor run" << std::endl;
    }

    std::shared_ptr<Widget> GetSharedObject(){
        // 如果返回this指针，生成新的控制块，相当于一个新的裸指针，引用计数不会加1
        // return std::shared_ptr<Widget>(this);
        return shared_from_this();
    }
};

int main()
{
  {
    std::shared_ptr<Widget> p(new Widget());
    std::cout << "the first p.use_count = " << p.use_count() << std::endl;
    //这里使用智能指针只是单纯的演示功能
    std::shared_ptr<Widget> q = p->GetSharedObject();
    // std::shared_ptr<Widget> q = p;

    std::cout << "the second p.use_count = " << p.use_count() << std::endl;
    std::cout << "the first q.use_count = " << q.use_count() << std::endl;

    q = p;
    std::cout << "after q = p" << std::endl;
    std::cout << "the third p.use_count = " << p.use_count() << std::endl;
    std::cout << "the second q.use_count = " << q.use_count() << std::endl;

    std::shared_ptr<Widget> sp = std::make_shared<Widget>();
    std::cout << "the first sp.use_count = " << sp.use_count() << std::endl;
    
    //经过sp = p之后，sp指向另一个地址
    //递增q指向的对象的引用计数
    //递减sp指向的对象的引用计数
    //sp原来指向的对象已没有了引用者，会自动释放
    sp = p;
    std::cout << "after sp = p" << std::endl;
    std::cout << "the fourth p.use_count = " << p.use_count() << std::endl;
    std::cout << "the sp.use_count = " << sp.use_count() << std::endl;
    std::cout << "the q.use_count = " << q.use_count() << std::endl;

    //sp 和q 都指向同一个对象
    sp = p;
    std::cout << "**********after sp = p" << std::endl;
    std::cout << "the fourth p.use_count = " << p.use_count() << std::endl;
    std::cout << "the sp.use_count = " << sp.use_count() << std::endl;
    std::cout << "the q.use_count = " << q.use_count() << std::endl;

    q = sp;
    std::cout << "**********after q = sp" << std::endl;
    std::cout << "the fourth p.use_count = " << p.use_count() << std::endl;
    std::cout << "the sp.use_count = " << sp.use_count() << std::endl;
    std::cout << "the q.use_count = " << q.use_count() << std::endl;
  }
    return 0;
}