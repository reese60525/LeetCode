/*
 * 題目: https://leetcode.com/problems/word-search/description/

 * 題目解釋:
 * 給一個m * n大小的matrix，內容包含大小寫英文字母，再給一個string，讓你確認board中是否存在一個
 * 不重複的相連路徑組成的字串等於word，若存在則輸出true，反之false。

 * 思路:
 * 一開始想著用dp，但後來發現每個dp狀態之間並無固定關聯性，所以有些case會出錯，由於matrix大小最多為
 * 6 * 6，word長度最多15，因此用dfs + backtracking來暴力解釋最簡單且有效的方式。

 * 解法:
 * 把board每個元素當成開頭去跑dfs搜索答案，可以建立一些提前return的條件來優化backtracking，在這裡
 * 我使用了check function用來確認board中的letter數量能不能滿足word需求，以及翻轉word讓letter出現
 * 頻率低的為開頭。
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int ROWS, COLS;
    int direction[4][2] {
        {-1, 0 },
        {1,  0 },
        {0,  1 },
        {0,  -1}
    };

    // 優化backtracking algorithm，用來確認board中的letter數量能不能滿足word需求
    bool check(std::vector<std::vector<char>> &board, std::string &word, std::vector<int> &board_counts) {
        std::vector<int> word_counts(58, 0);

        for (auto i : board) { // 計算board中每種letter數量
            for (auto j : i) {
                ++board_counts[j - 'A'];
            }
        }
        for (auto i : word) {
            ++word_counts[i - 'A'];
            if (board_counts[i - 'A'] < word_counts[i - 'A']) // 數量不足以滿足word，輸出false
                return false;
        }

        return true;
    }

    // dfs走訪上下左右找尋答案
    bool dfs(int row, int col, int rank, std::string &word, std::vector<std::vector<char>> &board) {
        if (rank == word.length()) { // rank用以計算目前有多少letter和word相同，rank = word長度就是找到答案
            return true;
        }
        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) { // 邊界確認
            return false;
        }
        if (board[row][col] != word[rank]) { // letter不合
            return false;
        }

        char curr = board[row][col]; // 暫時存放當前letter
        board[row][col] = '0';       // 設定當前letter已經被走訪過
        for (auto dirs : direction) {
            if (dfs(row + dirs[0], col + dirs[1], rank + 1, word, board)) // recursion走訪
                return true;
        }
        board[row][col] = curr; // 復原當前letter

        return false;
    }

    bool exist(std::vector<std::vector<char>> &board, std::string word) {
        ROWS = board.size(), COLS = board[0].size();
        std::vector<int> board_counts(58, 0);

        if (word.length() > ROWS * COLS) { // 優化演算法，word比board還大
            return false;
        }
        if (!check(board, word, board_counts)) { // 優化演算法，判斷board能不能滿足word
            return false;
        }

        // 優化演算法，判斷word的開頭和結尾的letter在board中出現的頻率，在board出現得越多次的letter，找到該
        // letter的可能性 越大，所以要從出現頻率小的letter開始搜尋，可以更快排除不可能的路徑，優化搜尋過程
        if (board_counts[word.front() - 'A'] > board_counts[word.back() - 'A']) {
            reverse(word.begin(), word.end());
        }
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (dfs(i, j, 0, word, board)) { // 把每個board[][]當成開頭去搜索
                    return true;                 // 找到答案就輸出，後續不用做了
                }
            }
        }
        return false;
    }
};

int main() { return 0; }