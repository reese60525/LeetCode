/*
 *  Author      : Reese
 *  Created On  : 2024-12-20 23:59
 *  Description : https://leetcode.com/problems/longest-palindromic-substring/description/
 */

#include <cstddef>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// // dp
// class Solution {
//   public:
//     std::string longestPalindrome(std::string s) {
//         size_t n = s.length();
//         std::pair<size_t, size_t> res_index = {0, 0}; // 最長回文子字串的起始和終點 index
//         bool dp[n];
//         std::memset(dp, 0, sizeof(dp));

//         // i < n 是因為 size_t 是 unsigned int，所以 i 不會是負數
//         // 當 i 從 0 減 1 時，會變成 unsigned int 的最大值，因此迴圈判斷條件要為 i < n 而不是 i >= 0
//         for (size_t i = n - 1; i < n; --i) {
//             for (size_t j = n - 1; j > i; --j) {
//                 dp[j] = ((s[i] == s[j]) && (j - i < 3 || dp[j - 1]));
//                 if (dp[j] && (j - i) > (res_index.second - res_index.first)) {
//                     res_index = {i, j};
//                 }
//             }
//         }

//         return s.substr(res_index.first, res_index.second - res_index.first + 1);
//     }
// };

// // two pointer
// class Solution {
//   public:
//     std::string longestPalindrome(std::string s) {
//         std::pair<int, int> res_index = {0, 0}; // 最長回文子字串的起始index和終點index

//         for (int i = 0; i < s.length(); ++i) {
//             std::pair<int, int> sub_odd = findPalindromic(i, i, s);      // 奇數回文
//             std::pair<int, int> sub_even = findPalindromic(i, i + 1, s); // 偶數回文

//             // 若sub_odd比res_index長，則更新res_index
//             if ((res_index.second - res_index.first) < (sub_odd.second - sub_odd.first)) {
//                 res_index = sub_odd;
//             }
//             // 若sub_even比res_index長，則更新res_index
//             if ((res_index.second - res_index.first) < (sub_even.second - sub_even.first)) {
//                 res_index = sub_even;
//             }
//         }

//         // 將res_index轉成string
//         std::string res = "";
//         for (int i = res_index.first; i <= res_index.second; ++i) {
//             res += s[i];
//         }

//         return res;
//     }

//   private:
//     //  尋找以left和right為中心點的回文
//     std::pair<int, int> findPalindromic(int left, int right, std::string &s) {
//         int len = s.length();

//         // 判斷邊界條件和兩側字元是否相等
//         while (left > -1 && right < len && s[left] == s[right]) {
//             --left;
//             ++right;
//         }

//         // 因為while loop最後會多執行一次，所以left和right要各往中心退一格
//         return {left + 1, right - 1};
//     }
// };

// manacher's algorithm
class Solution {
  public:
    std::string longestPalindrome(std::string s) {
        // 將 string 轉換成 manacher's algorithm 的格式
        // e.g. s = "abba" -> str = "^#a#b#b#a#$"
        size_t n = s.length();
        std::string str(2 * n + 3, '#');
        str[0] = '^';
        str[2 * n + 2] = '$';
        for (size_t i = 0; i < n; ++i) {
            str[2 * i + 2] = s[i];
        }

        // max_right 為目前找到的回文子字串終點最右邊的 index，pivot 為 max_right 的回文中心點 index
        // max_i 為目前找到的最長回文子字串的中心點 index，max_len 為目前找到的最長回文子字串長度
        size_t pivot = 0, max_right = 0, max_i = 0, max_len = 0;
        // 用來儲存 str 中以 str[i] 為回文中心，從 str[i] 到回文子字串終點的長度
        std::vector<size_t> str_max_len(str.size(), 1);
        // 排除 ^ 和 $，index = [1, str.size() - 2]
        for (size_t i = 1; i < str.size() - 1; ++i) {
            // mirror_i 為 i 基於 pivot 的鏡像 index
            size_t mirror_i = 2 * pivot - i;
            // 利用已經算過的 str_max_len 來設定 str_max_len[i]
            if (i < max_right) {
                str_max_len[i] = std::min(str_max_len[mirror_i], max_right - i + 1);
            }

            // 試著擴展 str_max_len[i]
            while (str[i - str_max_len[i]] == str[i + str_max_len[i]]) {
                ++str_max_len[i];
            }

            // 若 str_max_len[i] 擴展到 max_right 之外，則更新 max_right 和 pivot
            if (i + str_max_len[i] - 1 > max_right) {
                max_right = i + str_max_len[i] - 1;
                pivot = i;
            }

            // 如果新的回文子字串長度大於 max_len，則更新 max_len 和 max_i
            if (str_max_len[i] > max_len) {
                max_len = str_max_len[i];
                max_i = i;
            }
        }

        return s.substr((max_i - max_len) / 2, max_len - 1);
    }
};

int main() {

    return 0;
}