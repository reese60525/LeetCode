/*
 * 題目: https://leetcode.com/problems/number-of-provinces/description/
 * 題目解釋:
 * 思路:
 * 解法:
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    int connect[200];
    int findRoot(int a) { return connect[a] == a ? a : connect[a] = findRoot(connect[a]); }
    int findCircleNum(std::vector<std::vector<int>> &isConnected) {
        int n = isConnected.size();

        for (int i = 0; i < n; ++i) {
            connect[i] = i;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (isConnected[i][j] == 1) {
                    connect[findRoot(i)] = findRoot(j);
                }
            }
        }

        int ans = 0;
        std::vector<bool> all_group(n, false);
        for (int i = 0; i < n; ++i) {
            int i_root = findRoot(i);
            if (!all_group[i_root]) {
                all_group[i_root] = true;
                ++ans;
            }
        }
        return ans;
    }
};
int main() { return 0; }