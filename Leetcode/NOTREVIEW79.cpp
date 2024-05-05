#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int pre_index = -1;
    bool exist(std::vector<std::vector<char>> &board, std::string word) {
        // 確認board的字母數量有沒有>=word所需要的字母數量
        if (pre_index == -1) {
            std::unordered_map<char, int> letter_table;
            for (auto i : board)
                for (auto j : i)
                    ++letter_table[j];
            for (auto i : word)
                if (letter_table[i] == 0)
                    return false;
                else
                    --letter_table[i];
        }
        // 遞迴找解
        if (word.length() == 0 && pre_index != -1)
            return true;
        char word_0 = word[0];
        word.erase(0, 1);
        for (int i = 0; i < board.size() * board[0].size(); ++i) {
            char letter = board[i / board[0].size()][i % board[0].size()]; // 當前board的letter
            if ((letter == word_0) &&
                (pre_index == -1 || (abs(i - pre_index) == 1 && (i / board[0].size() == pre_index / board[0].size())) ||
                 abs(i - pre_index) == board[0].size())) { // 要和word_0相同字母，且要有相連(上下左右)
                int temp = pre_index;
                pre_index = i;
                board[i / board[0].size()][i % board[0].size()] = '0';
                if (exist(board, word))
                    return true;
                // 恢復資料
                pre_index = temp;
                board[i / board[0].size()][i % board[0].size()] = letter;
            }
        }
        return false;
    }
};
// data test
// 3 4 ABCESFCSADEE ABCCED
// 3 4 ABCESFESADEE ABCESEEEFS
int main() {
    Solution solution;
    std::vector<std::vector<char>> board;
    std::string word;
    int i, j;
    std::cin >> i >> j;
    while (i--) {
        std::vector<char> temp;
        for (int k = 0; k < j; ++k) {
            char a;
            std::cin >> a;
            temp.push_back(a);
        }
        board.push_back(temp);
    }
    std::cin >> word;
    for (auto x : board) {
        for (auto y : x) {
            std::cout << y << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    std::cout << solution.exist(board, word) << '\n';
    return 0;
}
