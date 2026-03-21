
#include <type_traits>
#include <utility>

// a glvalue (“generalized” lvalue) is an expression whose evaluation determines
// the identity of an object or function;

template <class T>
struct is_prvalue : std::true_type {};
template <class T>
struct is_prvalue<T&> : std::false_type {};
template <class T>
struct is_prvalue<T&&> : std::false_type {};

template <class T>
struct is_lvalue : std::false_type {};
template <class T>
struct is_lvalue<T&> : std::true_type {};
template <class T>
struct is_lvalue<T&&> : std::false_type {};

// a glvalue that denotes an object whose resources can be reused;
template <class T>
struct is_xvalue : std::false_type {};
template <class T>
struct is_xvalue<T&> : std::false_type {};
template <class T>
struct is_xvalue<T&&> : std::true_type {};

struct A {
    int m;
};

A&& operator+(A, A);
A&& f();

int main() {

    int a{42};
    int& b{a};
    int&& r{std::move(a)};

    // Expression `42` is prvalue
    static_assert(is_prvalue<decltype((42))>::value);

    // Expression `a` is lvalue
    static_assert(is_lvalue<decltype((a))>::value);

    // Expression `b` is lvalue
    static_assert(is_lvalue<decltype((b))>::value);

    // Expression `std::move(a)` is xvalue
    static_assert(is_xvalue<decltype((std::move(a)))>::value);

    // Type of variable `r` is rvalue reference
    static_assert(std::is_rvalue_reference<decltype(r)>::value);

    // Type of variable `b` is lvalue reference
    static_assert(std::is_lvalue_reference<decltype(b)>::value);

    // Expression `r` is lvalue
    static_assert(is_lvalue<decltype((r))>::value);

    // ------------------------

    A a1;
    A&& ar = static_cast<A&&>(a1);

    // Function call with return type rvalue reference is xvalue
    static_assert(is_xvalue<decltype((f()))>::value);

    // Member of object expression, object is xvalue, `m` is a non-static data
    // member
    static_assert(is_xvalue<decltype((f().m))>::value);

    // A cast expression to rvalue reference
    static_assert(is_xvalue<decltype((static_cast<A&&>(a1)))>::value);

    // Operator expression, whose return type is rvalue reference to object
    static_assert(is_xvalue<decltype((a1 + a1))>::value);

    // Expression `ar` is lvalue, `&ar` is valid
    static_assert(is_lvalue<decltype((ar))>::value);
    [[maybe_unused]] A* ap = &ar;
}