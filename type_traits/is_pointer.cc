#include <type_traits>

int main() {
    struct A {
        int m;
        void f() {}
    };

    int A::* mem_data_ptr = &A::m;    // a pointer to member data
    void (A::*mem_fun_ptr)() = &A::f; // a pointer to member function

    static_assert(!std::is_pointer<A>::value);
    static_assert(!std::is_pointer_v<A>);
    static_assert(!std::is_pointer<A>());
    static_assert(!std::is_pointer<A>{});
    static_assert(!std::is_pointer<A>()());
    static_assert(!std::is_pointer<A>{}());
    static_assert(std::is_pointer_v<A*>);
    static_assert(std::is_pointer_v<A const* volatile>);
    static_assert(
        !std::is_pointer_v<decltype(mem_data_ptr)>); // false to pointer to
                                                     // member
    static_assert(
        !std::is_pointer_v<decltype(mem_fun_ptr)>); // false to pointer to
                                                    // member function
    static_assert(std::is_pointer_v<void*>);
    static_assert(!std::is_pointer_v<int>);
    static_assert(std::is_pointer_v<int*>);
    static_assert(std::is_pointer_v<int**>);
    static_assert(!std::is_pointer_v<int[10]>);
    static_assert(!std::is_pointer_v<std::nullptr_t>);
    static_assert(std::is_pointer_v<void (*)()>);
}