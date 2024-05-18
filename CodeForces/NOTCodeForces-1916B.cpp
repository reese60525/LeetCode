/*
 * 題目: https://codeforces.com/problemset/problem/1916/B
 * 題目解釋:
 * 思路:
 * 解法:
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

void printFunction1(int a, int b) {
    if (b == 1) {
        std::cout << a * a << '\n';
    }
    else {
        int k = 1;
        while (k++ && k <= b) {
            float n = 1.0 * a * k / b;
            if (n == int(n)) {
                if (n < b) {
                    std::cout << a * k << '\n';
                }
                else {
                    std::cout << a * b << '\n';
                }
                return;
            }
        }
    }
}
// 6 30 180 2*3 2*3*5 2*3*5

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        int a, b;
        std::cin >> a >> b;
        printFunction1(b, a);
    }
    return 0;
}
// 3 12 24
// 6 30