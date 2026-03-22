#include <iostream>
#include <type_traits>

class A {};

static_assert(std::is_rvalue_reference_v<A> == false and
              std::is_rvalue_reference_v<A&> == false and
              std::is_rvalue_reference_v<A&&> != false and
              std::is_rvalue_reference_v<char> == false and
              std::is_rvalue_reference_v<char&> == false and
              std::is_rvalue_reference_v<char&&> != false);

template <typename T>
void test(T&& x) {
    static_assert(std::is_same_v<T&&, decltype(x)>);
    std::cout << "T&&\t" << std::is_rvalue_reference<T&&>::value << std::endl;
    std::cout << "decltype(x)\t" << std::is_rvalue_reference<decltype(x)>::value
              << std::endl;
}

int main() {

    std::cout << std::boolalpha;
    std::cout << "A\t" << std::is_rvalue_reference<A>::value << std::endl;
    std::cout << "A&\t" << std::is_rvalue_reference<A&>::value << std::endl;
    std::cout << "A&&\t" << std::is_rvalue_reference<A&&>::value << std::endl;
    std::cout << "char\t" << std::is_rvalue_reference<char>::value << std::endl;
    std::cout << "char&\t" << std::is_rvalue_reference<char&>::value
              << std::endl;
    std::cout << "char&&\t" << std::is_rvalue_reference<char&&>::value
              << std::endl;

    std::cout << "\ntest(42)" << std::endl;
    test(42);

    std::cout << "\ntest(x)" << std::endl;
    int x = 42;
    test(x);
}