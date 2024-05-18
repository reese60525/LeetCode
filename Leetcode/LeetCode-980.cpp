/*
 * 題目: https://leetcode.com/problems/unique-paths-iii/description/
 *
 * 題目解釋:
 * 給一個matrix，value有-1、0、1、2，-1代表不能經過，0代表能經過，1為起始點，2為終點，找出可以經過
 * 所有格子(不包含-1)的路徑方法數。
 *
 * 思路:
 * 無法dp，m和n為matrix的大小，測資m <= 20、n <= 20，m * n <= 20，非常小，判斷可以暴力解，使用
 * backtracking來找出所有路徑。
 *
 * 解法:
 * 先計算要走幾格才算是走完所有格子，以及紀錄起始點和終點，把走過的地方值設為1代表走過了，當全部格子都走
 * 過了且目前index在終點，則res + 1。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    // count紀錄目前走幾格，total是總共要走幾格，用來確認是否有格子沒走過，res是合法路徑數，begin和end是起始結束的座標
    int count, total, res;

    void backTracking(int i, int j, std::vector<std::vector<int>> &grid) {
        // 邊界確認和目前位置是否能經過
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == -2 || grid[i][j] == -1)
            return;
        if (grid[i][j] == 2) {        // 當前位置為終點時
            if (count + 1 == total) { // 若所有格子都走過，則res + 1
                ++res;
            }
            return;
        }
        ++count;         // 表示目前這格已走過，走過的格子數量+1
        grid[i][j] = -2; // 標記目前位置已走過

        // 往四個方向去走，預先判斷邊界和格子是否能經過(非1和-1)
        backTracking(i - 1, j, grid); //  up
        backTracking(i + 1, j, grid); // down
        backTracking(i, j - 1, grid); // left
        backTracking(i, j + 1, grid); // right

        grid[i][j] = 0; // 狀態恢復
        --count;
    }

    int uniquePathsIII(std::vector<std::vector<int>> &grid) {
        int begin[2];
        count = total = res = 0;

        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] != -1) {
                    ++total;
                }
                if (grid[i][j] == 1) {
                    begin[0] = i, begin[1] = j;
                }
            }
        }
        backTracking(begin[0], begin[1], grid);
        return res;
    }
};
int main() {

    return 0;
}