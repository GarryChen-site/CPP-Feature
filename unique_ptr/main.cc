#include <utility>

template <typename T>
class unique_ptr {
  public:
    explicit unique_ptr(T* ptr = nullptr) : ptr_(ptr) {}

    ~unique_ptr() { delete ptr_; }

    unique_ptr(unique_ptr&& other) { ptr_ = other.release(); }

    unique_ptr& operator=(unique_ptr rhs) {
        rhs.swap(*this);
        return *this;
    }

    T* get() const { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    operator bool() const { return ptr_; }

    T* release() {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    void swap(unique_ptr& rhs) {
        using std::swap;
        swap(ptr_, rhs.ptr_);
    }

  private:
    T* ptr_;
};

class shape {};

int main() {
    unique_ptr<shape> ptr1{new shape{}};
    // unique_ptr<shape> ptr2{ptr1};
    unique_ptr<shape> ptr3;
    // ptr3 = ptr1;
    ptr3 = std::move(ptr1);
    unique_ptr<shape> ptr4{std::move(ptr3)};
}
