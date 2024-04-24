#include <cmath>
#include <iostream>
#include <string>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 把int轉乘string型態藉此判斷位數
bool is_Armstrong(int n) {
    std::string temp = std::to_string(n);
    int k = 0;
    for (int i = 0; i < temp.length(); ++i) {
        k += pow((temp[i] - '0'), temp.length());
    }
    if (n == k)
        return true;
    else
        return false;
}

int main() {
    int m, n, count = 0;
    std::cin >> m >> n;
    for (int i = m; i <= n; ++i) {
        if (is_Armstrong(i)) {
            ++count;
            std::cout << i << " ";
        }
    }
    if (count == 0)
        std::cout << "none";
    std::cout << '\n';
    return 0;
}