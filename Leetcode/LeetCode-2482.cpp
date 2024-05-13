/*
 * 解法:
 * 建立兩個vector，用來存放該行該列的1和0數量相減之值，遍歷grid，如果
 * row[i]或column[j]沒算過，就去算出來再把row[i] column[j]的值相加
 *，並賦值給grid[i][j]，也就是邊改grid邊build table。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    std::vector<std::vector<int>> onesMinusZeros(std::vector<std::vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();                    // m = row, n = column
        std::vector<int> row(m, 0x3f3f3f3f), column(n, 0x3f3f3f3f); // row and column 的 1_nums - 0_nums
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (row[i] == 0x3f3f3f3f) { // 如果row[i]沒算過，要先算出來。
                    row[i] = 0;
                    for (int k = 0; k < n; ++k) {
                        if (grid[i][k] == 0)
                            --row[i];
                        else
                            ++row[i];
                    }
                }
                if (column[j] == 0x3f3f3f3f) { // 如果row[i]沒算過，要先算出來。
                    column[j] = 0;
                    for (int k = 0; k < m; ++k) {
                        if (grid[k][j] == 0)
                            --column[j];
                        else
                            ++column[j];
                    }
                }
                grid[i][j] = row[i] + column[j];
            }
        }
        return grid;
    }
};
int main() { return 0; }