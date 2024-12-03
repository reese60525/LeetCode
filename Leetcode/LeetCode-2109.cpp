/*
 * 題目： https://leetcode.com/problems/adding-spaces-to-a-string/description/
 *
 * 題目解釋：
 * 給一個字串：s 和 integer array：spaces，spaces[i] 表示要在 s[spaces[i]] 之前插入一個 ' '，
 * 回傳插入全部空格後的 s。
 * e.g.
 * s = "LeetcodeHelpsMeLearn"，spaces = {8, 13, 15}。
 * 插入空格後的 s = "Leetcode Helps Me Learn"。
 *
 * 思路：
 * 創建字串 res 其大小為 s_size + spaces_size，用 two pointer：i 、 j 來遍歷 s 和 spaces，
 * 當 i = spaces[j] 表示要插入空格。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::string addSpaces(std::string s, std::vector<int> &spaces) {
        size_t s_size = s.size(), spaces_size = spaces.size(), spaces_index = 0;
        std::string res(s_size + spaces_size, ' '); // 初始化以空格填滿

        for (size_t i = 0; i < s.size(); ++i) {
            // 成功加入一個空格，並將 spaces_index 往後移
            if (spaces_index < spaces_size && i == spaces[spaces_index]) {
                ++spaces_index;
            }
            // 新字串其 index 為 i + spaces_index
            res[i + spaces_index] = s[i];
        }

        return res;
    }
};

int main() {

    return 0;
}