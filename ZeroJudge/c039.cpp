#include <cmath>
#include <iostream>
#include <unordered_map>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 建立hash table來做dp
std::unordered_map<int, int> table;

int findCircle(int n) {
    if (table[n] > 0) {
        return table[n];
    }
    if (n == 1) {
        return 1;
    }
    if (n % 2 == 0) {
        table[n] = findCircle(n / 2) + 1;
    }
    else {
        table[n] = findCircle(n * 3 + 1) + 1;
    }
    return table[n];
}

int main() {
    int i, j;
    while (std::cin >> i >> j) {
        int max = 0;
        std::cout << i << " " << j << " ";
        if (i > j) {
            std::swap(i, j);
        }
        for (int k = i; k <= j; ++k) {
            int temp = findCircle(k);
            max = max > temp ? max : temp;
        }
        std::cout << max << '\n';
    }
    return 0;
}