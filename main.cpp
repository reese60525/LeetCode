#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 1 2 3 4 5 6 k =4
// 4 3 2 1 5 6

int main() { return 0; }