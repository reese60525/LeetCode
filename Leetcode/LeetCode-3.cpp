/*
 * 題目：https://leetcode.com/problems/longest-substring-without-repeating-characters/
 *
 * 題目解釋：
 * 給一個string，找出最長不重複字元的sub string，回傳其長度。string的內容包含ascii code。
 * e.g. string：abcabcc，所求sub string為abc，return 3。string aaa，所求sub string
 * 為a，return 1。
 *
 * 思路：
 * 該方法為sliding window algorithm。
 * 用table紀錄每個字元最新出現的index，用一個變數紀錄當前sub string的起始index，如果當
 * 前出現的字元其上次出現的index位置在sub string的範圍內，代表當前字元為重複字元，而新的
 * sub string的起始index為當前字元的上個index+1。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int lengthOfLongestSubstring(std::string s) {
        int max_len = 0, left = 0; // left為sub string的起始index
        int char_table[128];       // 紀錄該字元最新出現的index，128為ascii code數量

        for (int &n : char_table) { // 初始化table
            n = -1;
        }

        for (int right = 0; right < s.length(); ++right) {
            // 如果該字元曾經出現過，且出現的位置在sub string的範圍內
            if (char_table[s[right]] >= left) {
                // sub string的起始index改為當前字元上個index+1
                // e.g. abcaecc，當i=3時，sub string為abc，sub string的起始index為1(b)
                left = char_table[s[right]] + 1;
            }
            max_len = std::max(max_len, right - left + 1); // 計算當前sub string的長度
            char_table[s[right]] = right;                  // 更新字元最新出現的index
        }

        return max_len;
    }
};

int main() {

    return 0;
}