#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int a[6];
    int b = 6;
    std::vector<int> c(6);

    std::cout << "TEST1" << '\n';
    for (int i = 0; i < sizeof(a) / 4; ++i)
        std::cout << i << ' ';
    std::cout << "\n\n";

    std::cout << "TEST2" << '\n';
    for (int i = -3; i < sizeof(a) / 4; ++i)
        std::cout << i << ' ';
    std::cout << "\n\n";

    std::cout << "TEST3" << '\n';
    std::cout << "c'size=" << c.size() << '\n';
    for (int i = -3; i < c.size(); ++i)
        std::cout << i << ' ';
    std::cout << "\n\n";

    std::cout << "TEST4" << '\n';
    for (int i = -3; i < b; ++i)
        std::cout << i << ' ';
    std::cout << "\n\n";

    std::cout << "TEST5" << '\n';
    for (int i = -3; i < 6; ++i)
        std::cout << i << ' ';

    return 0;
}