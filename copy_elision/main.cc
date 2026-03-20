
#include <iostream>

// clang++ -fno-elide-constructors -std=c++17 main.cc -o main
// clang++ -fno-elide-constructors -std=c++11 main.cc -o main11

// Instead of constructing a temporary and then copying/moving it into the
// destination, the compiler constructs the object directly in the
// destination's memory

struct Noisy {
    Noisy() { std::cout << "constructed at " << this << std::endl; }
    Noisy(const Noisy&) { std::cout << "copy-constructed" << std::endl; }
    Noisy(Noisy&&) { std::cout << "move-constructed" << std::endl; }
    ~Noisy() { std::cout << "destructed at " << this << std::endl; }
};

Noisy f() {
    Noisy v = Noisy();

    return v;
}

void g(Noisy arg) { std::cout << "&arg = " << &arg << std::endl; }

int main() {
    Noisy v = f();

    std::cout << "&v = " << &v << std::endl;

    g(f());
}
