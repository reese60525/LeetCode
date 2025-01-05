/*
 *  Author      : Reese
 *  Created On  : 2025-01-05 10:37
 *  Description : https://leetcode.com/problems/shifting-letters-ii/description/
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
    std::string shiftingLetters(std::string s, std::vector<std::vector<int>> &shifts) {
        // 遍歷 shifts，計算 diff
        int diff[s.size() + 1];
        std::memset(diff, 0, sizeof(diff));
        for (auto &shift : shifts) {
            int st = shift[0], ed = shift[1], op = shift[2];
            diff[st] += op ? 1 : -1;
            diff[ed + 1] += op ? -1 : 1;
        }

        // 遍歷 s 來計算每個字元的位移量
        int total_diff = 0;
        for (int i = 0; i < s.size(); ++i) {
            total_diff += diff[i];
            int k = s[i] - 'a';
            // 若 k 位移後是負數，則 mod 後要取正
            s[i] = ((k + total_diff) % 26 + 26) % 26 + 'a';
        }

        return s;
    }
};

int main() {

    return 0;
}