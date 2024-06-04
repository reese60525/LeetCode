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
// abbbaac bbbaac
// abababc bababc
class Solution {
  public:
    int countCompleteSubstrings(std::string word, int k) {
        int res = 0, n = word.length();

        for (int i = 0; i < n; ++i) {
            int count = 0;
            std::vector<bool> table(26, 0);

            for (int j = i; j < n; ++j) {
                if (!table[word[j] - 'a']) {
                    ++count;
                }
                if (count * k < j - i + 1) {
                    break;
                }
                if (i != j && (word[j] - word[j - 1] > 2 || word[j] - word[j - 1] < -2)) {
                    break;
                }
                if (count * k == j - i + 1) {
                    ++res;
                }
            }
        }

        return res;
    }
};

int main() {

    return 0;
}