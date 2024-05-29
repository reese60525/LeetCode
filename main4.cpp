/*
 * 題目:
 *
 * 題目解釋:
 *
 * 思路:
 *
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
    std::string a = "12345";
    std::cout << a << '\n';
    a.insert(0, 1, 'a');
    std::cout << a << '\n';

    return 0;
}