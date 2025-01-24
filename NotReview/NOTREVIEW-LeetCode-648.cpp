/*
 * 題目: https://leetcode.com/problems/replace-words/description/
 *
 * 題目解釋:
 *
 * 思路:
 *
 * 解法:
 *
 */
#include <iostream>
#include <unordered_map>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class TrieNode {
  public:
    std::unordered_map<char, TrieNode *> children;
    bool isEndWord = false;
};

class Trie {
  private:
    TrieNode *root = new TrieNode;

    void printHelper(TrieNode *node, const std::string &prefix) const {
        if (node == nullptr)
            return;

        for (const auto &pair : node->children) {
            std::cout << prefix << "|-- " << pair.first << std::endl;
            std::string newPrefix = prefix + "|   ";
            printHelper(pair.second, newPrefix);

            if (pair.second->isEndWord) {
                std::cout << newPrefix << "(end)" << std::endl;
            }
        }
    }

  public:
    void insert(const std::string &s) {
        TrieNode *node = root;

        for (const char &c : s) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode;
            }
            node = node->children[c];
        }
        node->isEndWord = true;
    }

    int findShortestPrefix(int i, int j, const std::string &s) {
        TrieNode *node = root;

        for (; i < j; ++i) {
            if (node->children.find(s[i]) == node->children.end()) {
                break;
            }
            node = node->children[s[i]];
            if (node->isEndWord) {
                return i + 1;
            }
        }
        return j;
    }

    void printTrie() const {
        std::cout << "(root)" << std::endl;
        printHelper(root, "");
    }
};

class Solution {
  public:
    std::string replaceWords(std::vector<std::string> &dictionary, std::string sentence) {
        std::string res = "";
        Trie trie;

        for (const std::string &s : dictionary) {
            trie.insert(s);
        }

        sentence += ' ';
        int n = sentence.length();
        int head = 0, tail = 0;
        for (; tail < n; ++tail) {
            if (sentence[tail] == ' ') {
                int index = trie.findShortestPrefix(head, tail, sentence);
                res += sentence.substr(head, index - head) + " ";
                head = tail + 1;
            }
        }

        res.pop_back();
        return res;
    }
};

int main() {

    return 0;
}