
#include <cstddef>
#include <iostream>
#include <stdexcept>

constexpr int factorial(int n) { return n <= 1 ? 1 : n * factorial(n - 1); }

constexpr int factorial_cxx14(int n) {
    int res = 1;
    while (n > 1) {
        res *= n--;
    }
    return res;
}

class conststr {
    const char* p;
    std::size_t sz;

  public:
    // a reference to a const char array of size N.
    template <std::size_t N>
    constexpr conststr(const char (&a)[N]) : p(a), sz(N - 1) {}

    constexpr char operator[](std::size_t n) const {
        return n < sz ? p[n] : throw std::out_of_range("");
    }

    constexpr std::size_t size() const { return sz; }
};

constexpr std::size_t countlower(conststr s, std::size_t n = 0,
                                 std::size_t c = 0) {
    return n == s.size()                ? c
           : 'a' <= s[n] && s[n] <= 'z' ? countlower(s, n + 1, c + 1)
                                        : countlower(s, n + 1, c);
}

template <int n>
struct constN {
    constN() { std::cout << n << std::endl; }
};

int main() {
    std::cout << "4! =";
    constN<factorial(4)> out1; // computed at compile time

    volatile int k = 8; // disallow optimization using volatile
    std::cout << k << "! = " << factorial(k)
              << std::endl; // computed at run time

    std::cout << "The number of lowercase letters in \"Hello, world!\" is ";
    constN<countlower("Hello, world!")>
        out2; // implicitly converted to conststr

    constexpr int a[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    constexpr int length_a = sizeof a / sizeof(int);

    std::cout << "Array of lenght " << length_a << " has elements: ";
    for (int i = 0; i < length_a; i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
