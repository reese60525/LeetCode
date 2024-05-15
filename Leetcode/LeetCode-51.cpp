/*
 * 題目: https://leetcode.com/problems/n-queens/
 *
 * 題目解釋:
 * 給一個數字n，在一個n * n的棋盤上排列出n個皇后，並讓這些皇后互相不在任何皇后的攻擊路徑上
 * ，請把所有"不重複"的組合存入2d vector中並return。

 * 思路:
 * 標準的backtracking algorithm題目，測資大小n<=9很適合暴力解，先了解如何判斷皇后的位置
 * 是否在其他皇后的攻擊路徑上，皇后的攻擊路徑為自身直行和橫列以及兩個對角線。因此只要去判斷當
 * 前的位置直行、橫列以及兩個對角線上有無其他皇后，如果都沒有其他皇后就可以把該位置當作一個合
 * 法的位置，並進入到搜索下個皇后的階段。
 *
 * 解法:
 * 首先處理不重複的部分，原本想法是用雙迴圈跑所有位置，當得到8個合法的queen後再去和目前res中
 * 的每個棋盤對比看看有沒有重複，但這樣做太花時間了，已知每行和每列只能有一個queen，因此讓code
 * 遞迴每次進入遞迴時只處理一個row，例如一開始row = 0，找到合法的位置後進入下一層遞迴時讓row+1
 * 這樣就能少一層迴圈，每個遞迴只要跑col迴圈找出所有可能，這樣不但速度快也不會有重複的問題，雙
 * 迴圈會重複的原因主要是因為上一層遞迴的row會重複visit目前的row，例如現在n = 6，假設我最後一
 * 個queen在(5, 7)，上一個queen在(4, 2)，完成res的pushback之後會回到上個遞迴，而此時該遞迴
 * 的row迴圈為row = 4，他會繼續跑雙迴圈並且找到(5,7)這個位置並進入下個遞迴，而下個遞迴會找到
 * (5, 7)這個位置，導致重複的棋盤，因此只要讓每一層遞迴只處理固定的row就不會有重複的問題。
 * 再來是判斷目前位置是否合法，由於每層遞迴的row都不同，因此不用判斷row，只要check col和對角線，
 * 有兩種方式，第一種是創建3個array來儲存當前位置的col和對角線是否有其他皇后，這種方式處理速度
 * 比較快，但需要較多記憶體空間，第二種是寫一個function跑迴圈來判斷當前位置是否合法，速度較慢但
 * 使用的記憶體空間較少。
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

    // // 用迴圈判斷目前位置是否合法
    // bool isSafe(int row, int col, const std::vector<std::string> &board) {
    //     for (int i = 0; i < board.size(); ++i) {
    //         if (board[i][col] == 'Q') { // 檢查col
    //             return false;
    //         }
    //         // 由於queen的row是依序由0到n-1，因此只要檢查目前位置到左上和右上的對角線就好
    //         if (row - i >= 0 && col - i >= 0 && board[row - i][col - i] == 'Q') {
    //             return false;
    //         }
    //         if (row - i >= 0 && col + i < board.size() && board[row - i][col + i] == 'Q') {
    //             return false;
    //         }
    //     }
    //     return true;
    // }

    void backTracking(int row, const int &n, std::vector<std::string> &board, std::vector<std::vector<std::string>> &res) {
        if (row == n) { // 皇后數量滿了
            res.emplace_back(board);
            return;
        }

        // 用array儲存每個col和對角線的狀態
        for (int col = 0; col < n; ++col) {
            // check目前位置的col和兩個對角線是否有其他queen
            if (!COLS[col] && !Diagonal1[row + col] && !Diagonal2[(n - 1) - (row - col)]) {
                // 設定走訪過的狀態
                COLS[col] = Diagonal1[row + col] = Diagonal2[(n - 1) - (row - col)] = true;
                board[row][col] = 'Q';

                backTracking(row + 1, n, board, res);
                // 還原狀態
                COLS[col] = Diagonal1[row + col] = Diagonal2[(n - 1) - (row - col)] = false;
                board[row][col] = '.';
            }

            // // 用迴圈判斷位置是否合法
            // if (isSafe(row, col, board)) {
            //     board[row][col] = 'Q';
            //     backTracking(row + 1, n, board, res);
            //     board[row][col] = '.';
            // }
        }
    }

    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::string> board(n, std::string(n, '.'));
        std::vector<std::vector<std::string>> res;
        // 根據棋盤大小更改vector的大小
        COLS.assign(n, false);
        Diagonal1.assign(2 * n - 1, false);
        Diagonal2.assign(2 * n - 1, false);
        // call backtracking
        backTracking(0, n, board, res);

        return res;
    }
};

int main() {
    Solution solution;
    solution.solveNQueens(9);
    return 0;
}