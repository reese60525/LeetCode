/*
 *  Author      : Reese
 *  Created On  : 2024-12-24 10:48
 *  Description : https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    void buildAdj(std::vector<std::vector<int>> &adj, const std::vector<std::vector<int>> &edges) {
        for (auto &edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
    }

    void findDiameter(std::vector<std::vector<int>> &adj, int pre, int cur, std::pair<int, int> &max, int diameter) {
        for (int &next : adj[cur]) {
            if (next != pre) {
                findDiameter(adj, cur, next, max, diameter + 1);
            }
        }
        if (max.first < diameter) {
            max.second = max.first;
            max.first = diameter;
        }
    }

    int minimumDiameterAfterMerge(std::vector<std::vector<int>> &edges1, std::vector<std::vector<int>> &edges2) {
        size_t n = edges1.size() + 1, m = edges2.size() + 1;
        std::vector<std::vector<int>> adj1(n), adj2(m);
        buildAdj(adj1, edges1);
        buildAdj(adj2, edges2);

        std::pair<int, int> max1(0, 0), max2(0, 0);
        findDiameter(adj1, -1, 0, max1, 0);
        findDiameter(adj2, -1, 0, max2, 0);

        std::cout << max1.first << " " << max1.second << std::endl;
        std::cout << max2.first << " " << max2.second << std::endl;

        max1.first = (max1.first + max1.second + 1) / 2;
        max2.first = (max2.first + max2.second + 1) / 2;

        return max1.first + max2.first + 1;
    }
};

int main() {

    return 0;
}