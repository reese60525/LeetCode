#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int a[5](1, 2, 3, 4, 5);
    int b[5](0, 0, 0, 0, 0);
    int c[5](0, 0, 0, 0, 0);
    int d[5](0, 0, 0, 0, 0);
    std::cout << "a_array:";
    for (auto i : a)
        std::cout << i << ' ';
    std::cout << "\nb_array:";
    for (auto i : b)
        std::cout << i << ' ';

    std::copy_n(std::begin(a), 3, std::begin(b));
    std::cout << "\nnew b_array:";
    for (auto i : b)
        std::cout << i << ' ';

    return 0;
}