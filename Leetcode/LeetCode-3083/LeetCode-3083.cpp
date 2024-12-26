/*
 *  Author      : Reese
 *  Created On  : 2024-12-26 11:26
 *  Description : https://leetcode.com/problems/existence-of-a-substring-in-a-string-and-its-reverse/description/
 */

#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// Hash Map and Bit Manipulation
class Solution {
  public:
    bool isSubstringPresent(std ::string s) {
        int mp[26] = {0};

        for (size_t i = 0; i < s.size() - 1; ++i) {
            int a = s[i] - 'a', b = s[i + 1] - 'a';

            // 將 0x1 左移到第 b 個 bit 並與 mp[a] 做 bitwise OR
            mp[a] |= 1 << b;
            // 將 mp[b] 右移到第 a 個 bit 並與 0x1 做 bitwise AND
            if ((mp[b] >> a) & 1) {
                return true;
            }
        }

        return false;
    }
};

// // Hash Map
// class Solution {
//   public:
//     bool isSubstringPresent(std ::string s) {
//         std::bitset<26> mp[26];

//         for (size_t i = 0; i < s.size() - 1; ++i) {
//             int a = s[i] - 'a', b = s[i + 1] - 'a';

//             mp[a][b] = true;
//             if (mp[b][a]) {
//                 return true;
//             }
//         }

//         return false;
//     }
// };

int main() {

    return 0;
}