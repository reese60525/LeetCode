/*
 *  Author      : Reese
 *  Created On  : 2024-12-31 15:20
 *  Description : https://leetcode.com/problems/number-of-operations-to-make-network-connected/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// Union Find
class Solution {
  public:
    int makeConnected(int n, std::vector<std::vector<int>> &connections) {
        // 判斷連接線的數量是否足夠連接所有電腦
        if (connections.size() < n - 1) {
            return -1;
        }

        // parent 紀錄每個節點的父親， rank 紀錄每個 root 的 高度（深度）
        int parent[n], rank[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 1;
        }

        // 找 root 以及路徑壓縮
        auto find = [&](auto &&find, int x) -> int {
            return x == parent[x] ? x : parent[x] = find(find, parent[x]);
        };

        // 對每個邊進行處理
        for (auto &v : connections) {
            int root_x = find(find, v[0]);
            int root_y = find(find, v[1]);

            // 按照 rank 來合併，樹高較矮的合併到樹高較高的
            if (rank[root_x] > rank[root_y]) {
                std::swap(root_x, root_y);
            }
            parent[root_x] = root_y;
            // 如果兩個樹的 rank 一樣，則合併後的樹高需要 + 1
            rank[root_y] += rank[root_x] == rank[root_y];
        }

        // 計算不同連通分量的數量
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += parent[i] == i;
        }

        // 需要連接的線數為連通分量數量 - 1
        return res - 1;
    }
};

// DFS
// class Solution {
//   public:
//     int makeConnected(int n, std::vector<std::vector<int>> &connections) {
//         // 判斷連接線的數量是否足夠連接所有電腦
//         if (connections.size() < n - 1) {
//             return -1;
//         }

//         // 建立鄰接表
//         std::vector<bool> visited(n, false);
//         std::vector<std::vector<int>> adj(n);
//         for (auto &v : connections) {
//             adj[v[0]].push_back(v[1]);
//             adj[v[1]].push_back(v[0]);
//         }

//         // DFS 走訪所有節點
//         auto dfs = [&](auto &&dfs, int cur) {
//             if (visited[cur]) {
//                 return;
//             }

//             visited[cur] = true;
//             for (int next : adj[cur]) {
//                 if (!visited[next]) {
//                     dfs(dfs, next);
//                 }
//             }
//         };

//         int res = 0;
//         for (int i = 0; i < n; ++i) {
//             // 若當前節點未被走訪過，表示這是一個新的連通分量
//             res += !visited[i];
//             dfs(dfs, i);
//         }

//         // 需要連接的線數為連通分量數量 - 1
//         return res - 1;
//     }
// };

int main() {

    return 0;
}