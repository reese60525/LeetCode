#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int a = 0, input;
    while (std::cin >> input) {
        a *= 10;
        a += input;
        std::cout << a << '\n';
    }
    return 0;
}