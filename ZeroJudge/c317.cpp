#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int x, a, b, n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> a >> b;
        int count_a = x / a; // 從大硬幣的最大數量去找
        while (true) {
            if (count_a < 0) {
                std::cout << "-1" << '\n';
                break;
            }
            int count_b = (x - a * count_a) / b;
            if (a * count_a + b * count_b == x) {
                std::cout << count_a + count_b << '\n';
                break;
            }
            else {
                --count_a;
            }
        }
    }
    return 0;
}