
#include <cassert>
#include <type_traits>

static_assert(!std::is_member_pointer_v<int*>);

struct S {
    int i{42};
    int foo() { return 0xF00; }
};

using mem_int_ptr_t = int S::*;
using mem_fun_ptr_t = int (S::*)();
static_assert(std::is_member_pointer_v<mem_int_ptr_t>);
static_assert(std::is_member_pointer_v<mem_fun_ptr_t>);

int main() {
    S s;

    mem_int_ptr_t pm = &S::i;
    assert(s.i == s.*pm);

    mem_fun_ptr_t pmf = &S::foo;
    assert((s.*pmf)() == s.foo());
}