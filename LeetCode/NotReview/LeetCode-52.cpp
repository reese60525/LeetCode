/*
 * 題目: https://leetcode.com/problems/n-queens/
 *
 * 題目解釋:
 * 給一個數字n，在一個n * n的棋盤上排列出n個皇后，並讓這些皇后互相不在任何皇后的攻擊路徑上
 * ，請找出所有"不重複"的組合數量並return。

 * 思路:
 * 標準的backtracking algorithm題目，測資大小n<=9很適合暴力解，先了解如何判斷皇后的位置
 * 是否在其他皇后的攻擊路徑上，皇后的攻擊路徑為自身直行和橫列以及兩個對角線。因此只要去判斷當
 * 前的位置直行、橫列以及兩個對角線上有無其他皇后，如果都沒有其他皇后就可以把該位置當作一個合
 * 法的位置，並進入到搜索下個皇后的階段。
 *
 * 解法:
 * 和上一題LeetCode 51幾乎一樣。
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
    // 公式:n, Diagonal的大小為[2n-1]
    // 座標(x, y)其對角線index=>左上到右下的線:array[x+y], 左下到右上的線:array[(n-1)-(x-y)]
    // 例如一個4 * 4的棋盤，(3, 0)的Diagonal1 index為3，Diagonal2 index為6，(2,3)為5和4。
    std::vector<bool> COLS, Diagonal1, Diagonal2;
    int total;

    void backTracking(int row, const int &n) {
        if (row == n) { // 皇后數量滿了
            ++total;
            return;
        }

        // 用array儲存每個col和對角線的狀態
        for (int col = 0; col < n; ++col) {
            // check目前位置的col和兩個對角線是否有其他queen
            if (!COLS[col] && !Diagonal1[row + col] && !Diagonal2[(n - 1) - (row - col)]) {
                // 設定走訪過的狀態
                COLS[col] = true;
                Diagonal1[row + col] = true, Diagonal2[(n - 1) - (row - col)] = true;
                backTracking(row + 1, n);
                // 還原狀態
                COLS[col] = false;
                Diagonal1[row + col] = false, Diagonal2[(n - 1) - (row - col)] = false;
            }
        }
    }
    int totalNQueens(int n) {
        total = 0;
        // 用來判斷狀態的vector，根據棋盤大小更改vector的大小
        COLS.assign(n, false);
        Diagonal1.assign(2 * n - 1, false);
        Diagonal2.assign(2 * n - 1, false);
        // call backtracking
        backTracking(0, n);

        return total;
    }
};

int main() {
    Solution s;
    std::cout << s.totalNQueens(10);
    return 0;
}