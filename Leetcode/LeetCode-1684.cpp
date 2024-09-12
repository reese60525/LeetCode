/*
 * 題目: https://leetcode.com/problems/count-the-number-of-consistent-strings/description/
 *
 * 題目解釋:
 * 給一個string allowed和一組strings words，找出符合以下要求的string，string內所有的character都要包含在
 * allowed中，並計算有多少個符合要求的string。
 *
 * 思路:
 * 用一個array儲存allowed中出現過的character當作table使用，再用雙迴圈一一檢查words中每個string並計算符合
 * 要求的string數量。
 *
 * 解法:
 * 同上。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int countConsistentStrings(std::string allowed, std::vector<std::string> &words) {
        int ans = 0;
        int table[26] = {0};

        for (char c : allowed) { // 建立allowed所包含character的table
            table[c - 'a'] = 1;
        }

        for (std::string &v : words) {
            bool check = true; // 用來確認該string是否符合要求
            for (char &c : v) {
                if (!table[c - 'a']) { // 如果該character沒出現在allowed中就跳出迴圈
                    check = false;
                    break;
                }
            }
            if (check) {
                ++ans;
            }
        }

        return ans;
    }
};

int main() {

    return 0;
}