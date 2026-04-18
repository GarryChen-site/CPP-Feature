#include <iostream>
#include <iterator>
#include <ostream>
#include <utility>
#include <vector>

class stream {

  public:
    using flags_type = int;

  public:
    flags_type flags() const { return flags_; }

    // Replace flags_ with newf and return the old value
    flags_type flags(flags_type newf) { return std::exchange(flags_, newf); }

  private:
    flags_type flags_ = 0;
};

void f() { std::cout << "f()"; }

int main() {

    stream s;

    std::cout << s.flags() << std::endl;
    std::cout << s.flags(12) << std::endl;
    std::cout << s.flags() << std::endl;
    std::cout << std::endl;

    std::vector<int> v;

    // std::exchange(v, std::vector<int>{1, 2, 3, 4})
    std::exchange(v, {1, 2, 3, 4});

    std::copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
    std::cout << std::endl;

    void (*fun)();

    // std::exchange(fun, static_cast<void(*)()>(f))
    std::exchange(fun, f);
    fun();

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Fibonacci sequence: ";

    for (int a{0}, b{1}; a < 100; a = std::exchange(b, a + b)) {
        std::cout << a << ", ";
    }
    std::cout << "..." << std::endl;
}