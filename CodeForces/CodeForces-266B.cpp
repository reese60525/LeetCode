/*
 * 題目: https://codeforces.com/problemset/problem/266/B
 * 題目解釋:
 * 思路:
 * 解法:
 */
#include <algorithm>
#include <iostream>
#include <string>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {

    int n, t;
    while (std::cin >> n >> t) {
        std::string s;
        std::cin >> s;
        while (t--) {
            for (int i = 0; i < s.length() - 1; ++i) {
                if (s[i] == 'B' && s[i + 1] == 'G') {
                    std::swap(s[i], s[i + 1]);
                    ++i;
                }
            }
        }
        std::cout << s << '\n';
    }
    return 0;
}
// 01101001
// 01100101 2
// 01100011 2
// 00111011 3
// 00011111 4