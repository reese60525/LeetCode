/*
 * 題目: https://leetcode.com/problems/count-complete-substrings/description/
 *
 * 題目解釋:
 *
 * 思路:
 *
 * 解法:
 *
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int countCompleteSubstrings(std::string word, int k) {
        int res = 0, n = word.length();

        for (int i = 1; i < 27; ++i) {
            int c = 0, cur_size = 0, check = 0, window_size = k * i;
            int occurrence[26] {0}; // 計算目前window的字母出現次數

            if (window_size > n) {
                break;
            }

            for (int j = 0; j < n; ++j) {
                fun(c, check, k, occurrence[word[j] - 'a'], '+');

                ++occurrence[word[j] - 'a'];

                if (cur_size < window_size) {
                    ++cur_size;
                }
                else {
                    fun(c, check, k, occurrence[word[j - window_size] - 'a'], '-');
                    --occurrence[word[j - window_size] - 'a'];
                }

                if (cur_size == window_size && i == c && check == 0) {
                    ++res;
                }
                if (j != n - 1 && std::abs(word[j] - word[j + 1]) > 2) {
                    c = cur_size = check = 0;
                    memset(occurrence, 0, sizeof(occurrence));
                }
            }
        }

        return res;
    }

  private:
    void fun(int &c, int &check, const int &k, const int &occurrence, char op) {
        if (op == '+') {
            if (occurrence == 0) {
                ++c;
            }
            else if (occurrence == k) {
                ++check;
            }
        }
        else if (op == '-') {
            if (occurrence == 1) {
                --c;
            }
            else if (occurrence == k + 1) {
                --check;
            }
        }
    }
};

int main() {

    return 0;
}