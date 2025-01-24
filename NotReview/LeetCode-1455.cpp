/*
 * 題目： https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/description/
 *
 * 題目解釋：
 * 給兩個 string：sentence and searchWord，sentence 為數個不同的 word 以空格分開組成，
 * 如果有一個sentence 中的 word 其 prefix = searchWord，則 return 該 word 是 sentence
 * 中第幾個 word，若找不到 return -1。
 * e.g.
 * sentence = "hellohello hellohellohello"，searchWord = "ell"
 * 雖然 "ell" 在 sentence 中出現過數次，但都不是一個 word 的 prefix，所以 return -1。
 * sentence = "i love eating burger"，searchWord = "burg"
 * "burg" 為 word："burger" 的 prefix，"burger" 是 sentence 中 第 4 個 word，return 4。
 *
 * 思路：
 * 可以將 sentence 中的 word 一個一個提取出來和 searchWord 比對。
 * 在這個題目中 KMP algorithm 的效率不一定好，因為 KMP 適用於關鍵字可以出現在搜尋的
 * 字串中任何一個位置，而題目要求關鍵字需要為 word prefix，因此 KMP 不適合。
 * 假設要搜尋字串長度為 l，word average length = m，k = 關鍵字長度，
 * 將 word 從 sentence 取出並和關鍵字比對的時間複雜度為 O(l/m * k)，
 * KMP 則是 O(l+k)，k 為 LPS_table 建表的時間複雜度。
 * 假設 l = 1000、m = 5、k = 3，直接比對需要(1000/5 * 3) = 600，
 * KMP 需要 (1000 + 3) = 1003，直接比對會比 KMP 更有效率。
 */
#include <iostream>
#include <sstream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int isPrefixOfWord(std::string sentence, std::string searchWord) {
        int word_count = 0;
        std::istringstream word_stream(sentence);
        std::string word;

        while (word_stream >> word) {
            ++word_count;

            if (!word.compare(0, searchWord.size(), searchWord)) {
                return word_count;
            }
        }
        return -1;
    }
};

int main() {

    return 0;
}