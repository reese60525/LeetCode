/*
 * 解法: 一個一個字去比較。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    bool isValid(std::string word) {
        int count = 0;
        bool check[2] = {false, false};
        // vowel(母音)是true，consonant(子音)是false;
        bool letter_check_table[26] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
        for (auto i : word) {
            if ((i - 'a' > -1 && i - 'a' < 26)) {
                if (letter_check_table[i - 'a'])
                    check[0] = true;
                else
                    check[1] = true;
            }
            else if ((i - 'A' > -1 && i - 'A' < 26)) {
                if (letter_check_table[i - 'A'])
                    check[0] = true;
                else
                    check[1] = true;
            }
            else if (!(i - '0' > -1 && i - '0' < 10)) {
                return false;
            }
            ++count;
        }
        return (count > 2 && check[0] && check[1]);
    }
};
int main() { return 0; }