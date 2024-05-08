/*
 * 解法:
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int n;
    std::string input;
    while (std::cin >> n >> input) {
        int i = 0, j = 0, len = input.length();
        while (i + j < len) {
            std::cout << input[i + j];
            i += n;
            j++;
        }
        std::cout << '\n';
    }
    return 0;
}