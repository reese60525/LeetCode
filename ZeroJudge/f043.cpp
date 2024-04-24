#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int a, b, r;
    while (std::cin >> r >> a) {
        if (r == a) {
            if (a <= 6)
                std::cout << a - 3 << '+' << 3 << '=' << r << '\n';
            else
                std::cout << 3 << '+' << a - 3 << '=' << r << '\n';
        }
        else if (a < r - a) {
            std::cout << a << '+' << r - a << '=' << r << '\n';
        }
        else {
            std::cout << r - a << '+' << a << '=' << r << '\n';
        }
    }
    return 0;
}