/*
 *  Author      : Reese
 *  Created On  : 2024-12-26 11:26
 *  Description : https://leetcode.com/problems/existence-of-a-substring-in-a-string-and-its-reverse/description/
 */

#include <iostream>
#include <unordered_map>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 'a' 的二進位：01100001
// 'z' 的二進位：01111010

class Solution {
  public:
    bool isSubstringPresent(std ::string s) {
        std::unordered_map<int, bool> mp;

        for (size_t i = 0; i < s.size() - 1; ++i) {
            int a = s[i], b = s[i + 1];
            mp[(a << 10) + b] = true;
            if (mp.find((b << 10) + a) != mp.end()) {
                return true;
            }
        }

        return false;
    }
};

int main() {

    return 0;
}