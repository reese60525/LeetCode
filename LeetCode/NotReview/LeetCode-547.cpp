/*
 * 題目: https://leetcode.com/problems/number-of-provinces/description/
 *
 * 題目解釋:
 * 給一個matrix，matrix[i][j]代表i和j相連狀況，如果matrix[i][j] = 1，代表i、j相連，如果是0則不相連，
 * 求所有相連的Group數量，例如(1, 3, 5)、(2, 4, 6)、(7, 8, 9, 0)，總共3個Group。
 *
 * 思路:
 * 用一個vector存放vec[i]和誰相連，遍歷matrix，若matrix[i][j] = 1，則把i的root和j的root相連，最後再
 * 遍歷vec，找出每個city的root，計算不重複出現的root數量，可得到答案。
 *
 * 解法:並查集
 * 自己和別人相連 = 把自己的root和對方的root相連。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    // parent[x] = y代表x和y相連
    std::vector<int> parent, rank;
    // 找root，connect[a] = findRoot(parent[a])可以壓縮節點和root的路徑
    int findRoot(int a) {
        //  return parent[a] == a ? a : parent[a] = findRoot(parent[a]);
        while (parent[a] != a) {
            parent[a] = parent[parent[a]];
            a = parent[a];
        }
        return a;
    }
    // 把root相連，按照"秩"來決定root誰連誰，可以在大測資縮短tree高度
    void unionRoots(int x, int y) {
        int rootX = findRoot(x);
        int rootY = findRoot(y);
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        }
        else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        }
        else {
            parent[rootX] = rootY;
            ++rank[rootY];
        }
    }
    int findCircleNum(std::vector<std::vector<int>> &isConnected) {
        int n = isConnected.size();
        // 根據isConnect的size調整connect的size
        parent.resize(n);
        rank.resize(n, 0);
        // init connect，讓city開始和自己相連
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        // 把相連的city其root連起來，由於isConnected[i][j] == isConnected[j][i]，所以j迴圈從i+1開始
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isConnected[i][j] == 1) {
                    unionRoots(i, j);
                }
            }
        }
        // 計算共有幾個group
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (i == parent[i]) {
                ++ans;
            }
        }
        return ans;
    }
};

int main() { return 0; }