#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int ans = 0;
    int longestSubstring(std::string s, int k) {
        int letters_count[26];
        bool check = true;
        std::string temp = "";
        std::vector<std::string> sub_string;
        // initialize table
        memset(letters_count, 0, sizeof(letters_count));
        // build table
        for (auto i : s)
            ++letters_count[i - 'a'];
        // build substring vector
        for (auto i : s) {
            if (letters_count[i - 'a'] != 0 && letters_count[i - 'a'] < k) {
                // 表示s不合法，得拆分成substring繼續遞迴找解
                check = false;
                if (temp.length() > 0)
                    sub_string.push_back(temp);
                temp = "";
            }
            else
                temp += i;
        }
        // 用來存入s[end]也合法的string
        sub_string.push_back(temp);
        // 若s全都合法，則輸出答案
        if (check) {
            ans = s.length();
            return ans;
        }
        // 把sub_string中的string以長度排序(大到小)
        std::ranges::sort(sub_string, std::greater {}, &std::string::size);
        // 遞迴找解
        for (auto i : sub_string) {
            if (ans >= i.length())
                break;
            int temp = longestSubstring(i, k);
            ans = ans > temp ? ans : temp;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    std::string s;
    int k;
    while (std::cin >> s >> k) {
        solution.ans = 0;
        std::cout << solution.longestSubstring(s, k) << '\n';
    }
    return 0;
}

// //暴力解，從長度為s.length()開始找解
//  #include <algorithm>
//  #include <iostream>

// static const auto io_sync_off = []() {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     return nullptr;
// }();

// class Solution {
//   public:
//     int check(int letters_count[26], int k) {
//         int sum = 0;
//         for (int i = 0; i < 26; ++i) {
//             sum += letters_count[i];
//             if (letters_count[i] > 0 && letters_count[i] < k)
//                 return -1;
//         }
//         return sum;
//     }

//     int longestSubstring(std::string s, int k) {
//         int letters_count[26];
//         memset(letters_count, 0, sizeof(letters_count));

//         for (auto i : s)
//             ++letters_count[i - 'a'];

//         for (int i = s.length(); i > 0; --i) {
//             int round = s.length() - i + 1, left = 0, right = i - 1, temp[26];
//             std::copy(std::begin(letters_count), std::end(letters_count), std::begin(temp));
//             for (int j = i; j < s.length(); ++j) {
//                 --temp[s[j] - 'a'];
//             }
//             while (round--) {
//                 int ans = check(temp, k);
//                 if (ans != -1)
//                     return ans;
//                 if (round == 0)
//                     break;
//                 --temp[s[left] - 'a'];
//                 ++left;
//                 ++right;
//                 ++temp[s[right] - 'a'];
//             }
//         }

//         return 0;
//     }
// };

// int main() {
//     Solution solution;
//     std::string s;
//     int k;
//     while (std::cin >> s >> k)
//         std::cout << solution.longestSubstring(s, k) << '\n';
//     return 0;
// }
