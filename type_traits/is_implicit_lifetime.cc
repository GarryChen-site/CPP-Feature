// The following types are collectively called implicit-lifetime types:
// * scalar types:
//     * arithmetic types
//     * enumeration types
//     * pointer types
//     * pointer-to-member types
//     * std::nullptr_t
// * implicit-lifetime class types
//     * is an aggregate whose destructor is not user-provided
//     * has at least one trivial eligible constructor and a trivial,
//       non-deleted destructor
// * array types
// * cv-qualified versions of these types.
#include <type_traits>

#if __cplusplus >= 202603L

static_assert(
    std::is_implicit_lifetime_v<int>); // arithmetic type is a scalar type
static_assert(
    std::is_implicit_lifetime_v<const int>); // cv-qualified a scalar type

enum E { e };
static_assert(
    std::is_implicit_lifetime_v<E>); // enumeration type is a scalar type
static_assert(
    std::is_implicit_lifetime_v<int*>); // pointer type is a scalar type
static_assert(std::is_implicit_lifetime_v<std::nullptr_t>); // scalar type

struct S {
    int x, y;
};
// S is an implicit-lifetime class: an aggregate without user-provided
// destructor
static_assert(std::is_implicit_lifetime_v<S>);

static_assert(std::is_implicit_lifetime_v<int S::*>); // pointer-to-member

struct X {
    ~X() = delete;
};
// X is not implicit-lifetime class due to deleted destructor
static_assert(!std::is_implicit_lifetime_v<X>);

static_assert(std::is_implicit_lifetime_v<int[8]>); // array type
static_assert(
    std::is_implicit_lifetime_v<volatile int[8]>); // cv-qualified array type

#endif

int main() {}