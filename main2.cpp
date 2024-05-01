#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    std::string a = "666666";
    int *next = new int[a.length()];
    memset(next, 0, a.length() * sizeof(*next));
    std::cout << "666" << '\n';
    int b = a.length();
    for (int i = -2; i < b; ++i) {
        std::cout << "i=" << i << '\n';
    }
    for (int i = -3; i < 5; ++i)
        std::cout << i << ' ';
    return 0;
}