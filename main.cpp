/*
 *  Author      : Reese
 *  Created On  : 2024-12-26 21:42
 *  Description :
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class TreeAncestor {
  public:
    std::vector<int> p;
    std::vector<std::vector<int>> dp;
    TreeAncestor(int n, std::vector<int> &parent) {
        p = parent;
        dp.resize(n, std::vector<int>(n + 1, -2));
        for (size_t i = 0; i < n; ++i) {
            dp[i][0] = 1;
            dp[i][1] = parent[i];
        }
    }

    int getKthAncestor(int node, int k) {
        if (dp[node][k] == -2) {
            int cur = node, f = dp[node][0];
            cur = dp[node][f];
            for (size_t i = f + 1; i <= k; ++i) {
                if (cur == -1) {
                    dp[node][0] = i;
                    return -1;
                }
                cur = p[cur];
                dp[node][i] = cur;
            }
        }
        dp[node][0] = k;
        return dp[node][k];
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */

int main() {

    return 0;
}