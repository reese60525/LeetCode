/*
 * 解法:
 * 直接算兩字串每個字母出現次數，再用sort排序，一一比對是否字母出現次數相同
 * 如果全都相同則代表YES，反之NO。
 */
#include <algorithm>
#include <cstring>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    std::string input[2];
    while (std::cin >> input[0] >> input[1]) {
        int table[2][26];
        memset(table, 0, sizeof(table));
        for (int i = 0; i < input[0].length(); ++i) {
            ++table[0][input[0][i] - 'A'];
            ++table[1][input[1][i] - 'A'];
        }
        std::sort(table[0], table[0] + 26);
        std::sort(table[1], table[1] + 26);
        for (int i = 0; i < 26; ++i) {
            if (table[0][i] != table[1][i]) {
                std::cout << "NO" << '\n';
                break;
            }
            if (i == 25) {
                std::cout << "YES" << '\n';
            }
        }
    }
    return 0;
}