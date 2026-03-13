
#include <cstddef>
#include <iostream>

// Wraps T so the compiler cannot deduce T through it ("non-deduced context").
template <class T>
struct type_identity {
    using type = T;
};

template <class T>
using type_identity_t = typename type_identity<T>::type;

template <class T, std::size_t N>

struct MySpan {
    T *data_;
    static constexpr std::size_t size_ = N;
    // ── Constructor 1: from a raw C array by reference ────────────────────
    //
    //   T (&arr)[N]  means "reference to an array of N elements of type T".
    //
    //   Why NOT just  T* arr ?
    //     A pointer loses the size N — the compiler can't deduce it.
    //     A reference to an array keeps N as part of the type.
    //
    //   Why type_identity_t<T> instead of plain T?
    //     If we wrote  MySpan(T (&arr)[N])  the constructor itself would
    //     also try to deduce T, which conflicts with the class-level T and
    //     confuses overload resolution.
    //     Wrapping in type_identity_t<T> puts T in a non-deduced context:
    //     the constructor stops deducing T, leaving that solely to the
    //     CTAD guide below.
    //

    constexpr MySpan(type_identity<T> (&arr)[N]) noexcept : data_{arr} {}

    constexpr T *begin() const { return data_; }
    constexpr T *end() const { return data_ + N; }

    void print() const {
        for (std::size_t i = 0; i < N; i++) {
            std::cout << data_[i] << ' ';
        }
        std::cout << '\n';
    }
};

// ── CTAD Deduction Guide
// ──────────────────────────────────────────────────────
//
// Without this, writing  MySpan s{arr};  would fail: the compiler doesn't
// know which T and N to plug into MySpan<T,N>.
//
// The guide says:
//   "When you see  MySpan( T(&)[N] ),  deduce  MySpan<T, N>."
//
// Syntax:  TemplateName(args) -> DeducedType;
//

template <class T, std::size_t N>
MySpan(T (&)[N]) -> MySpan<T, N>;
