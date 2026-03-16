#include <concepts>
#include <cstddef>
#include <functional>
#include <string>

// Declaration of the concept “Hashable”, which is satisfied by any type “T”
// such that for values “a” of type “T”, the expression std::hash<T>{}(a)
// compiles and its result is convertible to std::size_t
template <typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

struct meow {};

template <Hashable T>
void f(T) {}

int main() {
    using std::operator""s;
    f("abc"s);
    // f(meow{});
}