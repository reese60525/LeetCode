/*
 * 解法:
 * 遇到ch就reverse，就這樣。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    void reverse_word(std::string &word, int end) {
        for (int i = 0; i < (end + 1) >> 1; ++i) {
            char temp = word[i];
            word[i] = word[end - i];
            word[end - i] = temp;
        }
    }
    std::string reversePrefix(std::string word, char ch) {
        for (int i = 0; i < word.length(); ++i) {
            if (word[i] == ch) {
                reverse_word(word, i);
                break;
            }
        }
        return word;
    }
};
int main() { return 0; }