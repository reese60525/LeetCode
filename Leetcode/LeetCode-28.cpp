/*
 * 題目： https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
 *
 * 題目解釋：
 * 給一個 string haystack 和 needle，如果 haystack 中有 substring = needle，回傳起始 index
 * 最小的 substring 之起始 index，如果沒有則 return -1。
 * e.g.
 * haystack = "sadbutsad"，needle = "sad"
 * substring 有兩個和 "sad" 相同，回傳起始 index 比較小的，也就是 0。
 *
 * 思路：
 * string 匹配問題可以用 KMP algorithm。
 * KMP algorithm的介紹：https://yeefun.github.io/kmp-algorithm-for-beginners/
 */
#include <iostream>
#include <string>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int strStr(std::string haystack, std::string needle) {
        // 如果 needle 比 haystack 還長，不可能匹配，return -1
        if (haystack.size() < needle.size()) {
            return -1;
        }

        // 建構 LPS(Longest Prefix and Suffix) table
        std::vector<int> LPS_table(needle.size(), 0);
        int j = 0; // LPS 的 index
        // i 從 1 開始，因為 needle 長度為 1 的 prefix 的 LPS 長度必為 0
        for (int i = 1; i < needle.size(); ++i) {
            // 如果不匹配，回退到上一個可能的 prefix 位置，從該位置繼續比對
            while (j > 0 && needle[i] != needle[j]) {
                j = LPS_table[j - 1];
            }

            // 如果匹配，增加 prefix 長度
            if (needle[i] == needle[j]) {
                ++j;
            }

            LPS_table[i] = j;
        }

        // 開始比對 haystack 和 needle
        j = 0; // needle 的 index
        for (int i = 0; i < haystack.size(); ++i) {
            // 如果不匹配，回退到上一個可能的 prefix 位置，從該位置繼續比對
            while (j > 0 && haystack[i] != needle[j]) {
                j = LPS_table[j - 1];
            }

            // 如果匹配，移動 needle 的 index
            if (haystack[i] == needle[j]) {
                ++j;
            }

            // 如果已經匹配整個 needle，return 起始 Iindex
            if (j == needle.size()) {
                return i - j + 1;
            }
        }

        // 沒有找到，return -1
        return -1;
    }
};

int main() {

    return 0;
}