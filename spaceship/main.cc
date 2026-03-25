#include <compare>
#include <iostream>
#include <set>

struct Point {
    int x;
    int y;

    auto operator<=>(const Point&) const = default;
};

int main() {
    Point pt1{1, 1}, pt2{2, 2};
    std::set<Point> s;
    s.insert(pt1);

    std::cout << std::boolalpha << (pt1 == pt2) << ' ' // false
              << (pt1 != pt2) << ' '                   // true
              << (pt1 < pt2) << ' '                    // true
              << (pt1 <= pt2) << ' '                   // true
              << (pt1 > pt2) << ' '                    // false
              << (pt1 >= pt2) << ' ';                  // false
}