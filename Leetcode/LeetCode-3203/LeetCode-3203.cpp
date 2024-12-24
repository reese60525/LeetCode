/*
 *  Author      : Reese
 *  Created On  : 2024-12-24 10:48
 *  Description : https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/description/
 */

#include <iostream>
#include <queue>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// DFS（樹狀DP）
// 將 adj 鄰接圖表創建為全域變數，這樣可以提高效能和降低記憶體使用率
// 如果是在 class 內創建，每次呼叫 class function 都得重新分配和釋放記憶體
const size_t N = 1e5 + 5;
std::vector<std::vector<int>> adj(N);

class Solution {
  public:
    int dfs(const std::vector<std::vector<int>> &adj, int pre, int cur, int &diameter) {
        int max_depth = 0; // 該節點的子樹最大深度

        for (const int &next : adj[cur]) {
            if (next == pre) {
                continue;
            }

            int temp = dfs(adj, cur, next, diameter);
            // 計算 diameter，每個子樹的 diameter 是深度最深的兩個分支相加
            diameter = std::max(diameter, max_depth + temp);
            // 更新最大深度
            max_depth = std::max(max_depth, temp);
        }

        // return 當前子樹的最大深度，例如 leaf node 會 return 0 + 1 = 1
        return max_depth + 1;
    }

    int findDiameter(const std::vector<std::vector<int>> &edges) {
        // node 的數量，題目說有 k 條邊，那麼就會有 k+1 個點
        size_t n = edges.size() + 1;
        // 由於 adj 是全域變數，要先清除先前的資料
        for (size_t i = 0; i < n; ++i) {
            adj[i].clear();
        }
        for (auto &edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        int diameter = 0;
        dfs(adj, -1, 0, diameter);
        return diameter;
    }

    int minimumDiameterAfterMerge(std::vector<std::vector<int>> &edges1, std::vector<std::vector<int>> &edges2) {
        int diameter1, diameter2, diameter3;

        diameter1 = findDiameter(edges1);
        diameter2 = findDiameter(edges2);
        diameter3 = (diameter1 + 1) / 2 + (diameter2 + 1) / 2 + 1;

        return std::max({diameter1, diameter2, diameter3});
    }
};

// // BFS
// // 將 adj 鄰接圖表創建為全域變數，這樣可以提高效能和降低記憶體使用率
// // 如果是在 class 內創建，每次呼叫 class function 都得重新分配和釋放記憶體
// const size_t N = 1e5 + 5;
// std::bitset<N> visited; // 紀錄是否走訪過
// std::vector<std::vector<int>> adj(N);

// class Solution {
//   public:
//     std::pair<int, int> bfs(size_t root) {
//         visited.reset();
//         std::queue<int> q;
//         q.push(root);

//         int level = 0, farthest_node;
//         while (!q.empty()) {
//             int q_size = q.size();
//             farthest_node = q.front();
//             for (size_t i = 0; i < q_size; ++i) {
//                 int node = q.front();
//                 q.pop();
//                 visited[node] = true;

//                 // 將所有相鄰節點加入 queue
//                 for (int &next : adj[node]) {
//                     // 如果已經走訪過，則跳過
//                     if (visited[next]) {
//                         continue;
//                     }
//                     q.push(next);
//                 }
//             }
//             ++level;
//         }

//         // 返回距離所以 level 要減 1
//         return {farthest_node, level - 1};
//     }

//     int findDiameter(const std::vector<std::vector<int>> &edges) {
//         // node 的數量，題目說有 k 條邊，那麼就會有 k+1 個點
//         size_t n = edges.size() + 1;
//         // 由於 adj 是全域變數，要先清除先前的資料
//         for (size_t i = 0; i < n; ++i) {
//             adj[i].clear();
//         }
//         for (auto &edge : edges) {
//             adj[edge[0]].push_back(edge[1]);
//             adj[edge[1]].push_back(edge[0]);
//         }

//         // 先取得 node 0 的最遠 node a，再以 a 為 root 取得最遠 node b 的距離
//         return bfs(bfs(0).first).second;
//     }

//     int minimumDiameterAfterMerge(std::vector<std::vector<int>> &edges1, std::vector<std::vector<int>> &edges2) {
//         int diameter1, diameter2, diameter3;

//         diameter1 = findDiameter(edges1);
//         diameter2 = findDiameter(edges2);
//         diameter3 = (diameter1 + 1) / 2 + (diameter2 + 1) / 2 + 1;

//         return std::max({diameter1, diameter2, diameter3});
//     }
// };

// // Topological sorting（Kahn's Algorithm）
// // 將 adj 鄰接圖表創建為全域變數，這樣可以提高效能和降低記憶體使用率
// // 如果是在 class 內創建，每次呼叫 class function 都得重新分配和釋放記憶體
// const size_t N = 1e5 + 5;
// std::vector<int> degree(N);
// std::vector<std::vector<int>> adj(N);

// class Solution {
//   public:
//     int KahnAlgorithm(size_t n) {
//         std::queue<int> q;
//         // 將所有 leaf node 加入 queue
//         for (size_t i = 0; i < n; ++i) {
//             if (degree[i] == 1) {
//                 q.push(i);
//             }
//         }

//         int level = 0; // 紀錄共幾層
//         // 最後會留下一個或兩個 node
//         while (n > 1) {
//             int q_size = q.size();
//             n -= q_size;
//             for (size_t i = 0; i < q_size; ++i) {
//                 int leaf_node = q.front();
//                 q.pop();

//                 // 將新的 leaf node 加入 queue
//                 for (int &node : adj[leaf_node]) {
//                     if (--degree[node] == 1) {
//                         q.push(node);
//                     }
//                 }
//             }

//             ++level;
//         }

//         return level * 2 + n - 1;
//     }

//     int findDiameter(const std::vector<std::vector<int>> &edges) {
//         // node 的數量，題目說有 k 條邊，那麼就會有 k+1 個點
//         size_t n = edges.size() + 1;
//         // 由於 adj 和 degree 是全域變數，要先清除先前的資料
//         for (size_t i = 0; i < n; ++i) {
//             adj[i].clear();
//             degree[i] = 0;
//         }
//         for (auto &edge : edges) {
//             adj[edge[0]].push_back(edge[1]);
//             adj[edge[1]].push_back(edge[0]);
//             ++degree[edge[0]];
//             ++degree[edge[1]];
//         }

//         return KahnAlgorithm(n);
//     }

//     int minimumDiameterAfterMerge(std::vector<std::vector<int>> &edges1, std::vector<std::vector<int>> &edges2) {
//         int diameter1, diameter2, diameter3;

//         diameter1 = findDiameter(edges1);
//         diameter2 = findDiameter(edges2);
//         diameter3 = (diameter1 + 1) / 2 + (diameter2 + 1) / 2 + 1;

//         return std::max({diameter1, diameter2, diameter3});
//     }
// };

int main() {

    return 0;
}