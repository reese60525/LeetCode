/*
 * 題目： https://leetcode.com/problems/valid-sudoku/description/
 *
 * 題目解釋：
 * 給一個 9x9 的 board 當作數獨的題目，判斷這個 board 是否為合法的數獨題目。
 * 一個合法的數獨題目有以下四點：
 * 1. 每行不可以有重複的 1 ~ 9。
 * 2. 每列不可以有重複的 1 ~ 9。
 * 3. 每個 3x3 的 block 中不可以有重複的 1 ~ 9。
 * 請注意，合法的數獨題目"不一定"有解!
 *
 * 思路：
 * 遍歷 board，並且用三個 9x9 的矩陣來儲存數獨題目的狀態，若遇到重複的數字表示該
 * 數獨題目是非法的。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    bool isValidSudoku(std::vector<std::vector<char>> &board) {
        // 遍歷 board，並且檢查是否有重複的數字
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    continue;
                }

                // 將數字轉換成數字 0 ~ 8 的 index
                int num = board[i][j] - '1';
                if (check_row[i][num] || check_col[j][num] || check_block[i / 3][j / 3][num]) {
                    return false;
                }
                check_row[i][num] = true;
                check_col[j][num] = true;
                check_block[i / 3][j / 3][num] = true;
            }
        }

        return true;
    }

  private:
    // 用來 check row column and block 中是否有重複的數字
    std::bitset<9> check_row[9];
    std::bitset<9> check_col[9];
    std::bitset<9> check_block[3][3];
};

int main() {

    return 0;
}