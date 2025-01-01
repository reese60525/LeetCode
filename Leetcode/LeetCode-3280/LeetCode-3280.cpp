/*
 *  Author      : Reese
 *  Created On  : 2025-01-01 11:11
 *  Description : https://leetcode.com/problems/convert-date-to-binary/description/
 */

#include <iostream>
#include <string>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// Mod
class Solution {
  public:
    std::string convertDateToBinary(std::string date) {
        // 將字串轉為整數
        int nums[3] = {(date[0] - '0') * 1000 + (date[1] - '0') * 100 + (date[2] - '0') * 10 + (date[3] - '0'),
                       (date[5] - '0') * 10 + (date[6] - '0'), (date[8] - '0') * 10 + (date[9] - '0')};

        // 將整數轉為二進制
        auto getBinary = [&](int num) -> std::string {
            std::string s = "";
            while (num > 0) {
                s = ((num & 1) == 0) ? '0' + s : '1' + s;
                num >>= 1;
            }
            return s;
        };

        return getBinary(nums[0]) + '-' + getBinary(nums[1]) + '-' + getBinary(nums[2]);
    }
};

// // Bit Manipulation
// class Solution {
//   public:
//     std::string convertDateToBinary(std::string date) {
//         // 將字串轉為整數
//         int nums[3] = {(date[0] - '0') * 1000 + (date[1] - '0') * 100 + (date[2] - '0') * 10 + (date[3] - '0'),
//                        (date[5] - '0') * 10 + (date[6] - '0'), (date[8] - '0') * 10 + (date[9] - '0')};

//         // 將整數轉為二進制
//         auto getBinary = [&](int num) -> std::string {
//             // 取得最高位數
//             int flag = 1 << (int)log2(num);
//             std::string s = "";
//             while (flag > 0) {
//                 // 若 num 在 flag 前導 1 的位置也是 1 則 c = '1' 反之 c = '0'
//                 char c = '0' + ((num & flag) > 0);
//                 s += c;
//                 flag >>= 1;
//             }
//             return s;
//         };

//         return getBinary(nums[0]) + '-' + getBinary(nums[1]) + '-' + getBinary(nums[2]);
//     }
// };

int main() {

    return 0;
}