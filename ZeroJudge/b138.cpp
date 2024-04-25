#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    std::vector<int> apple_tree;
    int high, apple_count = 0;
    for (int i = 0; i < 10; ++i) {
        int apple;
        std::cin >> apple;
        apple_tree.push_back(apple);
    }
    std::cin >> high;
    for (auto i : apple_tree) {
        apple_count += high + 30 >= i ? 1 : 0;
    }
    std::cout << apple_count << '\n';
    return 0;
}