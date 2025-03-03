/*
 *  Author      : Reese
 *  Created On  : 2025-02-24 10:07
 *  Description : https://leetcode.com/problems/most-profitable-path-in-a-tree/description/
 */

#include <iostream>
#include <vector>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,abm,bmi2")

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// chain forward star
struct edge {
    int ne;
    int to;
} e[int(2 * 10e5)];
int he[int(10e5)];
int inDegree[int(10e5)];
int idx;
class Solution {
  public:
    // 初始化 chain forward star
    Solution() {
        idx = 0;
        std::memset(he, -1, sizeof(he));
    }

    // 添加一條邊
    void add(int u, int v) {
        e[idx].ne = he[u];
        e[idx].to = v;
        he[u] = idx++;
    }

    auto mostProfitablePath(std::vector<std::vector<int>> &edges, int bob, std::vector<int> &amount) -> int {
        int n = amount.size();

        // 建立 chain forward star
        for (auto e : edges) {
            int u = e[0], v = e[1];
            add(u, v);
            add(v, u);
        }

        // 尋找 bob 走到 node 0 的路徑
        std::vector<int> path;
        bool isFind = false; // 用以判斷是否已經走到 node 0
        auto findPath = [&](this auto &&findPath, int parent, int cur) {
            path.push_back(cur);
            if (cur == 0) {
                isFind = true;
                return;
            }
            for (int i = he[cur]; i != -1; i = e[i].ne) {
                if (isFind) {
                    break;
                }
                if (e[i].to == parent) {
                    continue;
                }
                findPath(cur, e[i].to);
            }
            // 若當前的路徑並非走到 node 0 的路徑，則 pop element 來回溯
            if (!isFind) {
                path.pop_back();
            }
        };
        findPath(-1, bob);

        // 將 bob 走過的路徑的 amount 進行處理
        for (int i = 0; i < path.size() / 2; ++i) {
            amount[path[i]] = 0;
        }
        if (path.size() & 1) {
            amount[path[path.size() / 2]] /= 2;
        }

        // dfs 遍歷所有路徑，計算最大可得總值
        int res = INT_MIN;
        auto dfs = [&](this auto &&dfs, int parent, int cur, int sum) -> void {
            sum += amount[cur];
            int out_degree = 0; // out_degree = 1 的 node 為 leaf node
            for (int i = he[cur]; i != -1; i = e[i].ne) {
                ++out_degree;
                if (e[i].to == parent) {
                    continue;
                }
                dfs(cur, e[i].to, sum);
            }
            if (out_degree == 1 && cur != 0) {
                res = std::max(res, sum);
            }
        };
        dfs(-1, 0, 0);

        return res;
    }
};

auto main() -> int {

    return 0;
}