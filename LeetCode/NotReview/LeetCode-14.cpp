/*
 * 題目：https://leetcode.com/problems/longest-common-prefix/description/
 *
 * 題目解釋：
 * 給一組string array，求所有string的最長prefix。
 *
 * 思路：
 * 以第一個string為基準，從prefix[0]開始對strs中所有string比對。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::string longestCommonPrefix(std::vector<std::string> &strs) {
        std::string prefix = "";

        // 遍歷strs[0]，確認當前char是否為所有string的prefix
        for (int i = 0; i < strs[0].length(); i++) {
            // 遍歷strs
            for (int j = 1; j < strs.size(); j++) {
                if (strs[0][i] != strs[j][i]) {
                    return prefix;
                }
            }
            prefix += strs[0][i];
        }
        return prefix;
    }
};

int main() {

    return 0;
}