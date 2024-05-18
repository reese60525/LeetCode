/*
 * 題目: https://leetcode.com/problems/sudoku-solver/description/
 *
 * 題目解釋:
 * 給一組9x9的數獨，請解出答案，題目有說保證只有一組解答。
 *
 * 思路:
 * 使用backtracking來暴力解就好。
 *
 * 解法:
 * 用3個2D array來保存行、列、區塊的某數字是否存在，以此來確認數字1~9是否能進入下一層遞迴。
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
    bool row[9][9];
    bool col[9][9];
    bool block[9][9];
    // 確認目前的位置，num是否可以使用
    bool isValid(int i, int j, int num) {
        int k = (i / 3) * 3 + (j / 3);
        return !row[i][num] && !col[j][num] && !block[k][num];
    }
    // 標記目前位置已使用了num該數字，並update確認狀態的array
    void visit(int i, int j, int num) {
        int k = (i / 3) * 3 + (j / 3); // block的index算法
        row[i][num] = col[j][num] = block[k][num] = true;
    }
    // 和上面做相反的事情，取消標記
    void unvisit(int i, int j, int num) {
        int k = (i / 3) * 3 + (j / 3);
        row[i][num] = col[j][num] = block[k][num] = false;
    }
    // 不斷遞迴直到找到解
    bool backTracking(int i, int j, std::vector<std::vector<char>> &board) {
        if (i == 9) { // row = 9代表已經都做完了
            return true;
        }
        if (j == 9) { // 超出每行只有9格，更改i,j
            return backTracking(i + 1, 0, board);
        }
        if (board[i][j] != '.') { // 若是原本已經有數字了則跳過
            return backTracking(i, j + 1, board);
        }

        for (int num = 0; num < 9; ++num) { // 迭代數字1~9
            if (isValid(i, j, num)) {       // 該數字合法則可進入下一層遞迴
                visit(i, j, num);           // 標記目前位置已經使用了num
                board[i][j] = num + '1';
                if (backTracking(i, j + 1, board)) { // 當數獨找到解答則會一層一層return true
                    return true;                     // 不再進續往後找
                }
                unvisit(i, j, num); // 恢復狀態
                board[i][j] = '.';
            }
        }
        return false; // 若在for中都沒找到正解則return false，一般來說若數獨保證有解則不可能到這邊
    }

    void solveSudoku(std::vector<std::vector<char>> &board) {
        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        memset(block, 0, sizeof(block));

        // initialize array
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.') {
                    visit(i, j, board[i][j] - '1');
                }
            }
        }
        backTracking(0, 0, board);
    }
};

int main() {}