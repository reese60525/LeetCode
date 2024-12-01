/*
 * 題目： https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
 *
 * 題目解釋：
 * 給一個字串s和字串陣列words，求所有s中的substring，該substring包含words中所有word，，回傳符合要求的
 * substring的起始index。words中，的每個word長度都相同，並且可以有重複的word
 * e.g. s = “barfoothefoobarman”，words = {“foo”， “bar”}。
 * 在s中，符合要求的substring有兩個，分別是"barfoo"和"foobar"，因此回傳其起始index 0和9。
 *
 * 思路：
 * 由於words中每個word長度都相同，因此對於s可以把它以word的長度分割成數份，以上面的例子來看，
 * 從index = 0為起點開始，s可以被分割成{"bar", "foo", "the", "foo", "bar", man"}，
 * 如果是index = 1開始，s可以被分割成{"b", "arf", "oot", "hef", "oob, "arm", "an"}...
 * 以此類推，最多有word's length種分割方式，而在頭尾分割出來的字串可能不是一個完整長度的word，
 * 直接略過就行。
 * 首先用hash map:freq紀錄words中每個word的出現次數，之後對每個分割後的s來進行處理，創建
 * hash map:curr用來儲存分割後的s中遇到的word的出現次數。如果遇到的word不存在於words中，
 * 則包含這個word的substring都會是invalid的，所以要跳過這個word，從該word之後重新開始遍歷
 * ，curr也要reset。如果遇到的word是存在於words中，將curr對應的value +1，然後判斷該word的
 * 出現次數是否超過freq中的次數，如果超過的話則要將substring從第一個word開始將word移除，直到
 * 該word的出現次數等於freq的出現次數。如果當前substring包含words中所有word，則將substring
 * 的起始index push到res中。
 */
#include <iostream>
#include <unordered_map>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string> &words) {
        std::string_view S(s);
        int word_len = words[0].length();
        // 紀錄words中每個word的出現次數
        std::unordered_map<std::string_view, int> words_frequency;
        for (const std::string &word : words) {
            ++words_frequency[std::string_view(word)];
        }

        std::vector<int> res;
        for (int i = 0; i < word_len; ++i) {
            // substring的起始index和substring中的word數量
            int substring_head = i, words_count = 0;
            // 紀錄當前substring中每個word的出現次數
            std::unordered_map<std::string_view, int> curr_frequency;
            for (int j = i; j + word_len <= S.length(); j += word_len) {
                std::string_view word = S.substr(j, word_len);

                // 該word不在words中
                if (words_frequency.find(word) == words_frequency.end()) {
                    // substring起始index移動到下一個word的開頭
                    substring_head = j + word_len;
                    words_count = 0;
                    curr_frequency.clear();
                    continue;
                }

                // 該word在words中則將curr_frequency對應的value +1
                ++curr_frequency[word];
                ++words_count;

                // 該word在curr_frequency的出現次數大於words_frequency
                // 則要將該word在substring中第一次出現的word以及前面的其他word通通移除
                while (curr_frequency[word] > words_frequency[word]) {
                    // 取得substring中第一個word，將其出現次數-1，substring起始index移動到下一個word的開頭
                    std::string_view first_word = S.substr(substring_head, word_len);
                    --curr_frequency[first_word];
                    --words_count;
                    substring_head += word_len;
                }

                // 若當前substring的word數量和words的word數量相等，代表substring符合要求
                if (words_count == words.size()) {
                    res.push_back(substring_head);
                }
            }
        }

        return res;
    }
};

int main() {

    return 0;
}