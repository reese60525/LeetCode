/*
 * 題目： https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
 *
 * 題目解釋：
 *
 * 思路：
 *
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
        int word_len = words[0].length(), s_len = s.length();
        std::unordered_map<std::string, int> words_frequency;
        for (const std::string &word : words) {
            ++words_frequency[word];
        }

        std::vector<int> res;
        for (int i = 0; i < word_len; ++i) {
            int head = i, words_count = 0;
            std::unordered_map<std::string, std::queue<int>> words_index;
            for (int j = i; j < s_len; j += word_len) {
                if (j + word_len > s_len) {
                    break;
                }
                std::string word = s.substr(j, word_len);

                // 該word不在words中
                if (words_frequency.count(word) == 0) {
                    words_index.clear();
                    words_count = 0;
                    head = j + word_len;
                    continue;
                }

                words_index[word].push(j);
                ++words_count;

                // words_index中該word的數量等於words_frequency中該word的數量
                if (words_index[word].size() > words_frequency[word]) {
                    int idx = words_index[word].front();
                    head = idx + word_len;
                    for (auto &it : words_index) {
                        while (!it.second.empty() && it.second.front() <= idx) {
                            it.second.pop();
                            --words_count;
                        }
                    }
                }

                // 計算當前substring的word數量和words的word數量是否相等
                if (words_count == words.size()) {
                    res.push_back(head);
                    words_index[s.substr(head, word_len)].pop();
                    head += word_len;
                    --words_count;
                }
            }
        }

        return res;
    }
};

int main() {

    return 0;
}