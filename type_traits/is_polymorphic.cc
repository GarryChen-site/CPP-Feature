#include <type_traits>

struct A {
    int m;
};
static_assert(!std::is_polymorphic_v<A>);

struct B {
    virtual void foo();
};
static_assert(std::is_polymorphic_v<B>);

struct C : B {};
static_assert(std::is_polymorphic_v<C>);

struct D {
    virtual ~D() = default;
};
static_assert(std::is_polymorphic_v<D>);

// Uses inheritance, but not the virtual keyword:
struct E : A {};
static_assert(!std::is_polymorphic_v<E>);

struct F : virtual A {};
static_assert(!std::is_polymorphic_v<F>);

struct AX : A {};
struct AY : A {};
struct XY : virtual AX, virtual AY {};
static_assert(!std::is_polymorphic_v<XY>);

int main() {}
