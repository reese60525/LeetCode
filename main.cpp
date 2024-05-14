/*
 * 題目: https://leetcode.com/problems/path-with-maximum-gold/description/
 * 題目解釋:
 * 思路:
 * 解法:
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
    std::vector<std::vector<int>> dp;

    int recursion_solve(int pos, int cur, int count, std::vector<std::vector<int>> grid) {
        std::cout << "cur:" << cur << ", count" << count << '\n';
        int m = grid.size(), n = grid[0].size();
        int max_gold = 0, value = grid[cur / n][cur % n];
        std::cout << "row:" << cur / n << ", column:" << cur % n << '\n';
        if (pos != -1 && dp[cur][pos] > 0) {
            return dp[cur][pos];
        }
        if (grid[cur / n][cur % n] == 0) {
            return 0;
        }
        grid[cur / n][cur % n] = 0;
        if (cur - n > -1) {
            std::cout << "TEST1" << '\n';
            dp[cur][0] = recursion_solve(0, cur - n, count + 1, grid);
            max_gold = std::max(max_gold, dp[cur][0]);
        }
        if (cur + n < m * n) {
            std::cout << "TEST2" << '\n';
            dp[cur][1] = recursion_solve(1, cur - n, count + 1, grid);
            max_gold = std::max(max_gold, dp[cur][1]);
        }
        if (cur % n - 1 > -1) {
            std::cout << "TEST3" << '\n';
            dp[cur][2] = recursion_solve(2, cur - n, count + 1, grid);
            max_gold = std::max(max_gold, dp[cur][2]);
        }
        if (cur % n + 1 < n) {
            std::cout << "TEST4" << '\n';
            dp[cur][3] = recursion_solve(3, cur - n, count + 1, grid);
            max_gold = std::max(max_gold, dp[cur][3]);
        }
        return value + max_gold;
    }

    int getMaximumGold(std::vector<std::vector<int>> &grid) {
        int max_gold = 0, row = grid.size(), column = grid[0].size();
        dp.assign(row * column - 1, std::vector(4, 0));

        for (int i = 0; i < row * column; ++i) {
            int return_value = recursion_solve(-1, i, 0, grid);
            std::cout << return_value << '\n';
            max_gold = std::max(max_gold, return_value);
        }
        return max_gold;
    }
};
// {{1,0,7},{2,0,6},{3,4,5},{0,3,0},{9,0,20}}

int main() {
    Solution solution;
    std::vector<std::vector<int>> grid {
        {1, 0, 7 },
        {2, 0, 6 },
        {3, 4, 5 },
        {0, 3, 0 },
        {9, 0, 20}
    };
    std::cout << "ans:" << solution.getMaximumGold(grid);
    return 0;
}
