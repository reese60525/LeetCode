/*
 *  Author      : Reese
 *  Created On  : 2025-01-14 09:32
 *  Description : https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/description/
 */

#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int minSwaps(std::string &s) {
        int balance = 0;

        for (const char &c : s) {
            (c == '[') ? ++balance : --balance;
            balance = (balance < 0) ? 0 : balance;
        }

        return (balance + 1) >> 1;
    }
};

int main() {

    return 0;
}