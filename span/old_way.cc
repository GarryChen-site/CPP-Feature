// old_way.cc  — Pre-C++20: the classic "pointer + size" idiom
//
// Before std::span, passing a contiguous sequence meant carrying a raw pointer
// AND a length separately.  Every function had to do its own bounds checking,
// and there was no standard type to express a "view into an array".
//
// Compare with main.cc which uses std::span to do the same thing more safely.

#include <algorithm>
#include <cstddef>
#include <iostream>

// ---- slide -----------------------------------------------------------------
// Returns a sub-range [offset, offset+width) of the array.
// Caller is responsible for ensuring ptr/size are consistent.
struct Slice {
    const int* ptr;
    std::size_t size;
};

Slice slide(const int* ptr, std::size_t size,
            std::size_t offset, std::size_t width) {
    if (offset + width <= size) {
        return {ptr + offset, width};
    }
    return {nullptr, 0};   // empty slice — no standard "empty" sentinel
}

// ---- starts_with -----------------------------------------------------------
bool starts_with(const int* data, std::size_t data_size,
                 const int* prefix, std::size_t prefix_size) {
    if (data_size < prefix_size) return false;
    return std::equal(prefix, prefix + prefix_size, data);
}

// ---- ends_with -------------------------------------------------------------
bool ends_with(const int* data, std::size_t data_size,
               const int* suffix, std::size_t suffix_size) {
    if (data_size < suffix_size) return false;
    return std::equal(data + data_size - suffix_size, data + data_size,
                      suffix);
}

// ---- contains --------------------------------------------------------------
bool contains(const int* data, std::size_t data_size,
              const int* sub, std::size_t sub_size) {
    // std::search works on raw iterators too
    const int* result = std::search(data, data + data_size,
                                    sub, sub + sub_size);
    return result != data + data_size;
}

// ---- println ---------------------------------------------------------------
void println(const int* ptr, std::size_t size) {
    for (std::size_t i = 0; i < size; ++i)
        std::cout << ptr[i] << ' ';
    std::cout << '\n';
}

// ---- main ------------------------------------------------------------------
int main() {
    constexpr int a[]{0, 1, 2, 3, 4, 5, 6, 7, 8};
    constexpr int b[]{8, 7, 6};
    constexpr std::size_t a_size = sizeof(a) / sizeof(a[0]);
    constexpr std::size_t b_size = sizeof(b) / sizeof(b[0]);
    constexpr std::size_t width  = 6;

    // slide demo
    for (std::size_t offset = 0;; ++offset) {
        Slice s = slide(a, a_size, offset, width);
        if (s.ptr == nullptr) break;
        println(s.ptr, s.size);
    }

    // starts_with / ends_with / contains — same logic, uglier call sites
    bool ok =
        starts_with(a, a_size, a, 4)         &&
        starts_with(a + 1, 4, a + 1, 3)      &&
        !starts_with(a, a_size, b, b_size)   &&
        !starts_with(a, 8, a + 1, 3)         &&
        ends_with(a, a_size, a + 6, 3)       &&
        !ends_with(a, a_size, a + 6, 2)      &&
        contains(a, a_size, a + 1, 4)        &&
        !contains(a, 8, a, 9);

    // In C++11/14 we can't use static_assert with a runtime value;
    // just assert at runtime instead.
    if (!ok) {
        std::cerr << "Assertion failed!\n";
        return 1;
    }

    std::cout << "All checks passed.\n";
    return 0;
}
