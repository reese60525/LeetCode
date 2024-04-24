#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    long long m, n;
    while (std::cin >> n >> m) {
        //
        // if (m % 2 == 1 && n % 2 == 1)
        //     std::cout << (m - n) / 2 << '\n';
        // else
        //     std::cout << (m - n) / 2 + 1 << '\n';

        // 只用算術運算子的寫法，不用邏輯判斷
        int ans = (m - n) / 2 + 1 - (m % 2 + n % 2) / 2;
        std::cout << ans << '\n';
    }
    return 0;
}