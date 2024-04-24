#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int now, next;
    while (std::cin >> now >> next) {
        std::cout << (100 - (now - next)) % 100 << '\n';
    }
    return 0;
}
