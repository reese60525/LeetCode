/*
 * 題目： https://leetcode.com/problems/find-champion-ii/description/
 *
 * 題目解釋：
 *
 * 思路：
 *
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int findChampion(int n, std::vector<std::vector<int>> &edges) {
        bool teams[n];
        std::memset(teams, 1, sizeof(teams));

        for (auto &edge : edges) {
            teams[edge[1]] = false;
        }

        int res = -1;
        for (int i = 0; i < n; ++i) {
            if (teams[i]) {
                if (res != -1) {
                    return -1;
                }
                res = i;
            }
        }

        return res;
    }
};

int main() {

    return 0;
}