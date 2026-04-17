#include <type_traits>

template <typename T, typename U>
constexpr bool is_decay_equ = std::is_same_v<std::decay_t<T>, U>;

static_assert(is_decay_equ<int, int> && !is_decay_equ<int, float> &&
              is_decay_equ<int&, int> && is_decay_equ<int&&, int> &&
              is_decay_equ<const int&, int> && is_decay_equ<int[2], int*> &&
              !is_decay_equ<int[4][2], int*> &&
              !is_decay_equ<int[4][2], int**> &&
              is_decay_equ<int[4][2], int (*)[2]> &&
              is_decay_equ<int(int), int (*)(int)>);

int main() {}

/*
template<class T>
struct decay
{
private:
    typedef typename std::remove_reference<T>::type U;
public:
    typedef typename std::conditional<
        std::is_array<U>::value,
        typename std::add_pointer<typename std::remove_extent<U>::type>::type,
        typename std::conditional<
            std::is_function<U>::value,
            typename std::add_pointer<U>::type,
            typename std::remove_cv<U>::type
        >::type
    >::type type;
};
*/