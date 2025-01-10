/*
 *  Author      : Reese
 *  Created On  : 2025-01-10 09:51
 *  Description :
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// Trie
class Trie {
  private:
    int node_cnt = 0;
    Trie *next[26] = {nullptr};

  public:
    // 插入字串
    void insert(std::string &s) {
        Trie *cur = this;
        for (char &c : s) {
            if (cur->next[c - 'a'] == nullptr) {
                cur->next[c - 'a'] = new Trie();
            }
            cur = cur->next[c - 'a'];
            ++cur->node_cnt;
        }
    }

    // 返回以 s 為 prefix 的字串數量
    int search(std::string &s) {
        Trie *cur = this;

        for (char &c : s) {
            if (cur->next[c - 'a'] == nullptr) {
                return 0;
            }
            cur = cur->next[c - 'a'];
        }

        return cur->node_cnt;
    }
};

class Solution {
  public:
    int prefixCount(std::vector<std::string> &words, std::string pref) {
        Trie *root = new Trie();
        for (std::string &word : words) {
            root->insert(word);
        }

        return root->search(pref);
    }
};

// // 暴力解
// class Solution {
//   public:
//     int prefixCount(std::vector<std::string> &words, std::string pref) {
//         int res = 0;
//         for (std::string &word : words) {
//             for (int i = 0; i < pref.size(); ++i) {
//                 if (word[i] != pref[i]) {
//                     break;
//                 }
//                 if (i == pref.size() - 1) {
//                     ++res;
//                 }
//             }
//         }

//         return res;
//     }
// };

int main() {

    return 0;
}