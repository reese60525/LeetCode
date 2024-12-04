/*
 * 題目： https://leetcode.com/problems/sudoku-solver/description/
 *
 * 題目解釋：
 * 給一個 9x9 matrix 的數獨題目，保證剛好有一組解，完成這個數獨。
 *
 * 思路：
 * 使用backtracking來暴力解，並配合以下兩個方式來優化整體效率：
 * 1. 使用 bitset 來儲存每個 row, col, block 已經填入的數字，以加快檢查的速度。
 * 2. 使用 greedy algorithm 來決定下一個要填入的格子，從當前可以填充的格子中選擇
 *    能填充的數字選項最少的，這樣填錯的機率比較小，能減少回朔的次數。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    bool dfs(std::vector<std::vector<char>> &board, int remain) {
        // 剩餘 0 個格子可以填，表示完成數獨了
        if (remain == 0) {
            return true;
        }

        // 取得要填充的格子 index
        auto [i, j] = getNext(board);

        // 填入數字
        for (int num = 0; num < 9; ++num) {
            // 檢查該數字是否可以填入
            if (check_row[i][num] || check_col[j][num] || check_block[i / 3][j / 3][num]) {
                continue;
            }

            check_row[i][num] = true;
            check_col[j][num] = true;
            check_block[i / 3][j / 3][num] = true;
            board[i][j] = num + '1';

            if (dfs(board, remain - 1)) {
                return true;
            }

            check_row[i][num] = false;
            check_col[j][num] = false;
            check_block[i / 3][j / 3][num] = false;
            board[i][j] = '.';
        }

        return false;
    }

    // 找出未填充的格子中，可選擇的數字最少的格子，這樣填錯的機率小，需要回朔的次數也會減少
    std::pair<int, int> getNext(std::vector<std::vector<char>> &board) {
        int min_count = 10;
        std::pair<int, int> next_pos;

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                // 跳過已經填充的格子
                if (board[i][j] != '.') {
                    continue;
                }

                // 將當前格子的三個 bitset<9> 做 or 運算，會得到當前格子不能填入的數字的 bitset<9>
                // 接著做 not 運算，得到當前格子能填入的數字的 bitset<9>，用 count() 計算這些數字的數量
                int cur_count = ~(check_row[i] | check_col[j] | check_block[i / 3][j / 3]).count();
                if (cur_count < min_count) {
                    min_count = cur_count;
                    next_pos = {i, j};
                }
            }
        }

        return next_pos;
    }

    void solveSudoku(std::vector<std::vector<char>> &board) {
        // 初始化三個 bitset<9> 的 vector，這是用來紀錄每個 row, col, block 已經填入的數字
        int remain = 0; // 剩餘要填的格子數量
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    ++remain;
                    continue;
                }

                int num = board[i][j] - '1';
                check_row[i][num] = true;
                check_col[j][num] = true;
                check_block[i / 3][j / 3][num] = true;
            }
        }

        // 呼叫 dfs 開始填數字
        dfs(board, remain);
    }

  private:
    std::bitset<9> check_row[9];
    std::bitset<9> check_col[9];
    std::bitset<9> check_block[3][3];
};

int main() {

    return 0;
}