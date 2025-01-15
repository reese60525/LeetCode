/*
 *  Author      : Reese
 *  Created On  : 2025-01-15 09:25
 *  Description : https://leetcode.com/problems/minimize-xor/description/
 */

#include <bit>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// Bit manipulation 1
// class Solution {
//   public:
//     int minimizeXor(int &num1, int &num2) {
//         // 計算 num2 中 bit = 1 的數量
//         int cnt = std::popcount(static_cast<unsigned int>(num2));
//         // 計算 num1 中 bit = 1 的最高位置，例如 0b1101101 的最高位 1 在第 7 bit
//         int high = std::bit_width(static_cast<unsigned int>(num1));

//         // 將 1 填入 x，填入的位置從最高位依序對應到 num1 中 1 的 位置
//         int res = 0;
//         while (high-- > 0) {
//             res <<= 1;
//             // 確認是否還有 1 要填入 x 以及當前 num1 的 bit 是不是 1
//             if (cnt > 0 && num1 & (1 << high)) {
//                 ++res;
//                 --cnt;
//             }
//         }

//         // 將剩下的 1 從最低位依序填入 x
//         int flag = 1;
//         while (cnt > 0) {
//             // 確認當前 x 的 bit 是不是 0，0 的話可以填入 1
//             if (!(res & flag)) {
//                 res |= flag;
//                 --cnt;
//             }
//             flag <<= 1;
//         }

//         return res;
//     }
// };

// Bit manipulation 2
class Solution {
  public:
    int minimizeXor(int &num1, int &num2) {
        // 計算 num1 中 bit = 1 的數量
        int n1 = std::popcount(static_cast<unsigned int>(num1));
        // 計算 num2 中 bit = 1 的數量
        int n2 = std::popcount(static_cast<unsigned int>(num2));

        for (; n1 > n2; --n1) {
            num1 &= num1 - 1;
        }
        for (; n2 > n1; --n2) {
            num1 |= num1 + 1;
        }

        return num1;
    }
};

int main() {

    return 0;
}