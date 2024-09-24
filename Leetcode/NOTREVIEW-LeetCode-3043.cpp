/*
 * 題目: https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/description/
 *
 * 題目解釋:
 * 給兩組integer array，找出這兩組array各自任選一個integer配對，其prefix最大能為多少bit。
 *
 * 思路:
 * 使用Trie資料結構來解決，把array1當作預載資料insert至Trie中，再將array2當作要搜索的資料，
 * 丟入Trie去計算其最大prefix，把array2全搜尋一次後即可得答案。
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

// 解法1: Trie
class node {
  public:
    std::unordered_map<char, node *> children;
    bool isEnd = false;
};

class Trie {
  private:
    node *root = new node;

  public:
    void insert(std::string s) {
        node *current = root;
        for (char c : s) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new node;
            }
            current = current->children[c];
        }
        current->isEnd = true;
    }

    int findLongestPrefix(std::string s) {
        int count = 0;
        node *current = root;
        for (char c : s) {
            if (current->children.find(c) == current->children.end()) {
                break;
            }
            current = current->children[c];
            ++count;
        }
        return count;
    }
};

class Solution {
  public:
    int longestCommonPrefix(std::vector<int> &arr1, std::vector<int> &arr2) {
        int res = 0;
        Trie trie;

        for (int i : arr1) {
            trie.insert(std::to_string(i));
        }

        for (int i : arr2) {
            int count = trie.findLongestPrefix(std::to_string(i));
            res = std::max(res, count);
        }

        return res;
    }
};

// // 解法2: unordered_set (時間和空間更優)
// class Solution {
//   public:
//     int longestCommonPrefix(vector<int> &arr1, vector<int> &arr2) {
//         int res = 0;
//         std::unordered_set<int> prefixes;

//         for (int i : arr1) {
//             while (!prefixes.count(i) && i > 0) {
//                 prefixes.insert(i);
//                 i /= 10;
//             }
//         }

//         for (int i : arr2) {
//             while (!prefixes.count(i) && i > 0) {
//                 i /= 10;
//             }
//             if (i > 0) {
//                 res = std::max(res, static_cast<int>(log10(i) + 1));
//                 // static_cast<int> 用於將double轉為integer
//             }
//         }

//         return res;
//     }
// };

int main() {
    std::vector<int> arr1 {1, 10, 100}, arr2 {1000};
    Solution s;
    int ans = s.longestCommonPrefix(arr1, arr2);
    std::cout << "ans: " << ans << '\n';
    return 0;
}