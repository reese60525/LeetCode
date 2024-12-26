/*
 *  Author      : Reese
 *  Created On  : 2024-12-26 14:10
 *  Description : https://leetcode.com/problems/zigzag-conversion/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// Grouped Loop
class Solution {
  public:
    std::string convert(std::string s, int numRows) {
        // 能直接 return s 的情況
        if (numRows == 1 || s.length() <= numRows) {
            return s;
        }

        int t = numRows * 2 - 2; // 循環週期
        std::string res;
        res.reserve(s.length());
        for (size_t i = 0; i < numRows; ++i) {
            for (size_t j = 0; j + i < s.length(); j += t) {
                // 當前週期起點往下走 i 步就會得到第 i 列的第一個 element
                res += s[j + i];
                // 第一列和最後一列的一個週期一列只有一個 element，所以不能再加右邊的 element
                // 下個週期的起點往回走 i 步就會得到第 i 列的第二個 element
                if (i != 0 && i != numRows - 1 && j + t - i < s.length()) {
                    res += s[(j + t) - i];
                }
            }
        }

        return res;
    }
};

// // Simulation
// class Solution {
//   public:
//     std::string convert(std::string s, int numRows) {
//         // 能直接 return s 的情況
//         if (numRows == 1 || s.length() <= numRows) {
//             return s;
//         }

//         int cur_row = 0, dir = -1; // 初始row為第一層，dir為移動方向
//         std::vector<std::string> res(numRows);

//         for (int i = 0; i < s.length(); ++i) {
//             res[cur_row] += s[i];

//             // 判斷目前row是否處於邊界，是的話則要改變移動方向
//             if (cur_row == 0 || cur_row == numRows - 1) {
//                 dir *= -1;
//             }
//             cur_row += dir; // 移動至下一層row
//         }

//         // 將所有res[i]串接成到res[0]
//         for (int i = 1; i < numRows; ++i) {
//             res[0] += res[i];
//         }

//         return res[0];
//     }
// };

int main() {

    return 0;
}