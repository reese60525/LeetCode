/*
 * 題目: https://leetcode.com/problems/lexicographically-smallest-equivalent-string/description/
 *
 * 題目解釋:
 * 給一組長度相同的string s1 和 s2，相同位置的letter被視為equivalent characters，EX:s1 = "abc", s2 = "cde"，
 * 那麼'a' = 'c'且'c' = 'a'，'b' = 'd'且'd' = 'b'，'c' = 'e'且'e' = 'c'。利用這樣的關係，把baseStr的字串改為
 * 最小字典序，以上面的關係來舉例，baseStr = "eed"時，可以轉換為'e' = 'c'，'c' = 'a'，d' = 'b'，變成"aab"。如果
 * baseStr為"eedxyz"，則轉換後為"aabxyz"。
 *
 * 思路:
 * 可以把equivalent characters的關係視為分組，也就是把26個字母分成n組，典型的union-find問題，最多只有26組，題目難度低。
 *
 * 解法:
 * 典型的union-find解法，需要注意的是由於是找baseStr字典序組合，s1和s2的要使用rank的概念去改變root，也就是要比較誰的root
 * 比較小('a'小'z'大)。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    std::string smallestEquivalentString(std::string s1, std::string s2, std::string baseStr) {
        int parent[26];
        // initial parent
        for (int i = 0; i < 26; ++i) {
            parent[i] = i;
        }
        // unite s1 ans s2 letter
        for (int i = 0; i < s1.length(); ++i) {
            int x = s1[i] - 'a';
            int y = s2[i] - 'a';
            unionFind(x, y, parent);
        }
        // path compression
        for (int i = 0; i < 26; ++i) {
            findRoot(i, parent);
        }
        // change baseStr
        for (auto &i : baseStr) {
            int x = i - 'a';
            i = findRoot(x, parent) + 'a';
        }
        return baseStr;
    }

  private:
    int findRoot(int x, int parent[]) { // iterate寫法比遞迴節省空間
        while (x != parent[x]) {
            x = parent[x] = parent[parent[x]];
        }
        return x;
    }

    void unionFind(int x, int y, int parent[]) {
        int x_root = findRoot(x, parent);
        int y_root = findRoot(y, parent);

        if (x_root > y_root) { // compare root
            parent[x_root] = y_root;
        }
        else {
            parent[y_root] = x_root;
        }
    }
};
int main() {

    return 0;
}