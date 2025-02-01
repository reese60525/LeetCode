/*
 * 解法:
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
    std::vector<std::vector<int>> largestLocal(std::vector<std::vector<int>> &grid) {
        std::vector<std::vector<int>> ans(grid.size() - 2, std::vector<int>(grid.size() - 2));
        for (int i = 0; i < grid.size() - 2; ++i) {
            std::vector<int> temp;
            for (int j = 2; j < grid.size(); ++j) {
                ans[i][j - 2] = std::max({grid[i][j - 2], grid[i + 1][j - 2], grid[i + 2][j - 2], grid[i][j - 1], grid[i + 1][j - 1],
                                          grid[i + 2][j - 1], grid[i][j], grid[i + 1][j], grid[i + 2][j]});
            }
        }
        return ans;
    }
};
int main() { return 0; }