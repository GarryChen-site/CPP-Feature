
#include <memory>

class MyClass {
    std::weak_ptr<MyClass> weak_self_;

    MyClass() {}

  public:
    static std::shared_ptr<MyClass> create() {
        std::shared_ptr<MyClass> p(new MyClass());
        p->weak_self_ = p;
        return p;
    }

    // returns an empty shared_ptr if the object was already destroyed,
    // avoiding dangling pointer issues.
    std::shared_ptr<MyClass> getptr() { return weak_self_.lock(); }
};