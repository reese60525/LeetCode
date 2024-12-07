#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int lengthOfLongestSubstring(std::string s) {
        int max_len = 0, begin = 0; // begin 為 substring 的起始 index
        int char_table[128];        // 紀錄該字元最新出現的 index，128 為 ascii code 數量

        for (int &n : char_table) { // 初始化 hash table
            n = -1;
        }

        for (int i = 0; i < s.length(); ++i) {
            // 如果該字元上次出現的 index 在 substring 的範圍內
            if (char_table[s[i]] >= begin) {
                // substring 的起始 index 改為當前字元上次出現的 index + 1
                begin = char_table[s[i]] + 1;
            }
            max_len = std::max(max_len, i - begin + 1); // 計算當前sub string的長度
            char_table[s[i]] = i;                       // 更新字元最新出現的index
        }

        return max_len;
    }
};

int main() {

    return 0;
}