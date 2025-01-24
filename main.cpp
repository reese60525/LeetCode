/*
 *  Author      : Reese
 *  Created On  : 2025-01-23 18:55
 *  Description :
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

std::bitset<20005> state;
class Solution {
  public:
    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>> &graph) {
        state.reset();

        auto dfs = [&](auto &&dfs, int node) -> bool {
            if (state[node + 10000]) {
                return state[node];
            }
            state[node + 10000] = true;

            for (int &next : graph[node]) {
                if (!dfs(dfs, next)) {
                    return false;
                }
            }
            return state[node] = true;
        };

        std::vector<int> res;
        for (int i = 0; i < graph.size(); ++i) {
            if (dfs(dfs, i)) {
                res.push_back(i);
            }
        }

        return res;
    }
};

int main() {

    return 0;
}