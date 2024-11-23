/*
 * 題目： https://leetcode.com/problems/count-unguarded-cells-in-the-grid/description/
 *
 * 題目解釋：
 * 給定整數m,n表示matrix的大小，以及一組守衛和牆壁的值(x,y)，代表其在matrix中的位置，對於一個
 * 守衛而言，其上下左右延伸出去直到遇見牆壁的範圍，被當作是"可守衛區域"，請找出在這個matrix中的
 * "不可守衛區域"的數量。
 *
 * 思路：
 * 在matrix中，0表示"不可守衛區域"、1表示"可守衛區域"、2表示"牆壁或守衛"，遍歷每個守衛，沿著
 * 其上下左右開始填matrix，若當前matrix[x][y] = 0則填入1，直到遇到守衛或是牆壁，最後再計算
 * 共有幾個0，即為答案。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int countUnguarded(int m, int n, std::vector<std::vector<int>> &guards, std::vector<std::vector<int>> &walls) {
        int res = 0, matrix[m][n];

        // 初始化matrix為0，並將守衛和牆壁的位置改為2
        std::memset(matrix, 0, sizeof(matrix));
        for (int i = 0; i < walls.size(); i++) {
            matrix[walls[i][0]][walls[i][1]] = 2;
        }
        for (int i = 0; i < guards.size(); i++) {
            matrix[guards[i][0]][guards[i][1]] = 2;
        }

        // (dir[i], dir[i+1])表示方向，依序為上、右、下、左
        int dir[5] = {-1, 0, 1, 0, -1};
        for (int i = 0; i < guards.size(); i++) { // 遍歷每個守衛
            for (int j = 0; j < 4; ++j) {         // 遍歷守衛的上下左右
                int x = guards[i][0], y = guards[i][1];
                int d[] = {dir[j], dir[j + 1]}; // 方向
                // 當x,y沒有超出範圍且matrix[x][y]不是牆壁和守衛時，將matrix[x][y]改為1
                while (x + d[0] >= 0 && x + d[0] < m && y + d[1] >= 0 && y + d[1] < n &&
                       matrix[x + d[0]][y + d[1]] != 2) {
                    x += d[0];
                    y += d[1];
                    matrix[x][y] = 1;
                }
            }
        }

        // 計算matrix中0的數量
        for (auto &row : matrix) {
            res += std::count(row, row + n, 0);
        }

        return res;
    }
};

int main() {

    return 0;
}