/*
 * 題目:
 * 題目解釋:
 * 思路:
 * 解法:
 */
#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    static bool cmp(const std::vector<int> &x, const std::vector<int> &y) {
        return x[2] < y[2];
    }

    int spanningTree(int V, std::vector<std::vector<int>> adj[]) {
        int res = 0;
        std::vector<std::vector<int>> edges;
        std::vector<int> parent(V);

        for (int i = 0; i < V; ++i) {
            parent[i] = i;
        }

        for (int i = 0; i < V; ++i) {
            for (auto j : adj[i]) {
                edges.emplace_back(std::vector<int> {i, j[0], j[1]});
            }
        }

        std::sort(edges.begin(), edges.end(), cmp);

        for (auto edge : edges) {
            if (findRoot(edge[0], parent) != findRoot(edge[1], parent)) {
                unionFind(edge[0], edge[1], parent);
                res += edge[2];
            }
        }

        return res;
    }

  private:
    int findRoot(int x, std::vector<int> &parent) {
        while (x != parent[x]) {
            x = parent[x] = parent[parent[x]];
        }
        return x;
    }
    void unionFind(int x, int y, std::vector<int> &parent) {
        parent[findRoot(x, parent)] = findRoot(y, parent);
    }
};
int main() {

    return 0;
}