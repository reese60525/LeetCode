/*
 * 解法:
 *
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int n = 0;
    std::cin >> n;
    while (n--) {
        std::string input;
        std::cin >> input;
        int a = 0, b = 0;
        std::string c = "";
        for (int i = 4; i < 8; ++i) {
            a *= 10;
            a += input[i] - '0';
        }
        for (int i = 0; i < 3; ++i) {
            c += input[i];
        }
        b = (c[0] - 'A') * (26 * 26) + (c[1] - 'A') * 26 + (c[2] - 'A');
        if (abs(a - b) <= 100)
            std::cout << "nice" << '\n';
        else
            std::cout << "not nice" << '\n';
    }
    return 0;
}