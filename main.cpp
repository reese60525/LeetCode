/*
 * 題目:
 * 題目解釋:
 * 思路:
 * 解法:
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    struct cmp {
        bool operator()(const std::pair<int, int> &x, const std::pair<int, int> &y) {
            return x.second > y.second;
        }
    };

    int spanningTree(int V, std::vector<std::vector<int>> adj[]) {
        int res = 0, visited_count = 0;
        std::vector<bool> visited(V, 0);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, cmp> pq;

        pq.push({0, 0});
        while (!pq.empty() && visited_count < V) {
            int cur_node = pq.top().first;
            int weight = pq.top().second;
            pq.pop();

            if (visited[cur_node])
                continue;
            visited[cur_node] = true;
            res += weight;
            ++visited_count;

            for (auto i : adj[cur_node]) {
                if (!visited[i[0]]) {
                    pq.push({i[0], i[1]});
                }
            }
        }
        return res;
    }
};
int main() {

    return 0;
}