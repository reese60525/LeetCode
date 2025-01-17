/*
 *  Author      : Reese
 *  Created On  : 2025-01-17 12:17
 *  Description : https://leetcode.com/problems/neighboring-bitwise-xor/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    bool doesValidArrayExist(std::vector<int> &derived) {
        bool res = 0;
        for (const int &n : derived) {
            res ^= n;
        }

        return !res;
    }
};

int main() {

    return 0;
}