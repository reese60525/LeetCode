/*
 * 題目: https://leetcode.com/problems/unique-paths-ii/description/
 *
 * 題目解釋:
 * 給一個matrix，value為1代表障礙物，0則是可經過的位置，從index = (0, 0)開始走，只能往下或是
 * 往右邊走，求所有能不經過障礙物順利到達最右下角的路徑方法數。
 *
 * 思路:
 * 一開始使用backtracking來暴力解，但是由於matrix最大為100 * 100，暴力解會TLE，突然想到這題
 * 只能往下或是往右，和之前遇到的四種方向都能走的問題不同，並不會有重複路徑的問題(例如順時鐘繞一圈，
 * 導致該格的DP value有多種可能)，因此可以用DP來處理這問題。
 *
 * 解法:
 * 每次只能往右或往下走，當走到右下角後代表可走的路徑+1，所以return 1，用一個array存放當前位置往
 * 右或是往下走能有幾個可行路徑。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int dp[100][100]; // dp[i][j]，i和j為當前index
    int backTracking(int i, int j, std::vector<std::vector<int>>& grid) {
        if (i >= grid.size() || j >= grid[0].size() || grid[i][j] == 1) { // 邊界和障礙物確認
            return 0;
        }
        if (i == grid.size() - 1 && j == grid[0].size() - 1) { // 順利到右下角，路徑方法數+1
            return 1;
        }

        if (dp[i][j] < 0) {                                                         // dp< 0代表沒走過
            dp[i][j] = backTracking(i + 1, j, grid) + backTracking(i, j + 1, grid); // 遞迴拆解成子路徑，並把結果放入dp
        }
        return dp[i][j];
    }

    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        memset(dp, -1, sizeof(dp)); // initialize dp
        return backTracking(0, 0, obstacleGrid);
    }
};

int main() {

    return 0;
}