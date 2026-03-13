# span feature: compare new C++20 std::span vs old-school pointer+size idiom

# New way: C++20 std::span
add_executable(span_new main.cc)

# Old way: raw pointer + size
add_executable(span_old old_way.cc)
