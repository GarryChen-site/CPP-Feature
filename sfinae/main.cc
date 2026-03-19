#include <iostream>

template <int I>
struct X {};

template <template <class T> class>
struct Z {};

template <class T>
void f(typename T::Y*) {}

template <class T>
void g(X<T::N>*) {}

template <class T>
void h(Z<T::template TT>*) {}

struct A {};
struct B {
    int Y;
};
struct C {
    typedef int N;
};
struct D {
    typedef int TT;
};
struct B1 {
    typedef int Y;
};
struct C1 {
    static const int N = 0;
};
struct D1 {
    template <typename T>
    struct TT {};
};

// -----------------------------

// This overload is added to the set of overloads if C is
// a class or reference-to-class type and F is a pointer to member function of C
template <class C, class F>
auto test(C c, F f) -> decltype((void)(c.*f)(), void()) {
    std::cout << "(1) Class/class reference overload called" << std::endl;
}

// This overload is added to the set of overloads if C is a
// pointer-to-class type and F is a pointer to member function of C
template <class C, class F>
auto test(C c, F f) -> decltype((void)((c->*f)()), void()) {
    std::cout << "(2) Pointer overload called" << std::endl;
}

void test(...) { std::cout << "(3) Catch-all overload called" << std::endl; }

int main() {
    // f<A>(0); A does not contain a member Y
    // f<B>(0); The Y member of B is not a type
    // g<C>(0); The N member of C is not a non-type
    // h<D>(0); The TT member of D is not a template

    f<B1>(0);
    g<C1>(0);
    h<D1>(0);

    // -------------------

    struct X {
        void f() {}
    };
    X x;
    X& rx = x;
    test(x, &X::f);
    test(rx, &X::f);
    test(&x, &X::f);
    test(42, 1337);
}