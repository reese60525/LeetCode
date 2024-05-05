#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    // print table
    void printTable(std::vector<std::vector<std::vector<bool>>> table) {
        std::cout << "*************************************************" << '\n';
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                std::cout << "i:" << i << ", j:" << j << " => ";
                for (int k = 0; k < table[i][j].size(); ++k) {
                    std::cout << table[i][j][k] << ' ';
                }
                std::cout << '\n';
            }
        }
        std::cout << "*************************************************" << '\n';
    }

    void solveSudoku(std::vector<std::vector<char>> &board) {
        std::vector<std::vector<std::vector<bool>>> table;
        int empty_count = 0;
        // 找出board[i][j]的所有可能數字並填表
        for (int i = 0; i < 9; ++i) {
            std::vector<std::vector<bool>> temp1;
            for (int j = 0; j < 9; ++j) {
                std::vector<bool> temp2;
                if (board[i][j] != '.') {
                    temp1.push_back(std::vector<bool> {0, 0, 0, 0, 0, 0, 0, 0, 0});
                    continue;
                }
                ++empty_count;                                   // 計算有幾個空格
                std::cout << "i:" << i << ", j:" << j << " => "; // print (i,j)
                int block = (i / 3) * 3 + (j / 3);               // board[i][j]的block編號，由上而下由左而右為0、1、2、3...8
                for (int k = 1; k < 10; ++k) {
                    for (int x = 0; x < 9; ++x) {
                        if (board[i][x] == (k + '0') || board[x][j] == (k + '0') ||
                            board[(block / 3) * 3 + x / 3][(block % 3) * 3 + (x % 3)] == (k + '0')) {
                            temp2.push_back(0);
                            break;
                        }
                        if (x == 8) {
                            std::cout << k << ' '; // print k
                            temp2.push_back(1);
                        }
                    }
                }
                std::cout << '\n'; // print '\n'
                temp1.push_back(temp2);
            }
            table.push_back(temp1);
        }
        printTable(table);
        // 解數獨
        std::cout << "\n解數獨\n";
        while (empty_count) {
            int exception = 0; // 無窮迴圈處理，當沒有"唯一可能數"時就會離開while;
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (board[i][j] != '.')
                        continue;
                    int count = 0, num;
                    for (int k = 0; k < 9; ++k) {
                        if (count > 1)
                            break;
                        if (table[i][j][k] == 1) {
                            num = k; // ?i???r
                            ++count;
                        }
                    }
                    if (count == 1) { // 找到"唯一可能數"
                        ++exception;
                        --empty_count;
                        board[i][j] = num + 1 + '0';
                        int block = (i / 3) * 3 + (j / 3); // board[i][j]的block編號，由上而下由左而右為0、1、2、3...8
                        for (int x = 0; x < 9; ++x) {
                            table[i][x][num] = false;
                            table[x][j][num] = false;
                            table[(block / 3) * 3 + x / 3][(block % 3) * 3 + (x % 3)][num] = false;
                        }
                    }
                }
            }
            std::cout << "exception:" << exception << '\n';
            // printTable(table);
            if (exception == 0)
                break;
        }
    }
};

int main() {
    Solution solution;
    std::vector<std::vector<char>> board = {
        {'.', '.', '9', '7', '4', '8', '.', '.', '.'},
        {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
        {'.', '.', '7', '.', '.', '.', '2', '4', '.'},
        {'.', '6', '4', '.', '1', '.', '5', '9', '.'},
        {'.', '9', '8', '.', '.', '.', '3', '.', '.'},
        {'.', '.', '.', '8', '.', '3', '.', '2', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '6'},
        {'.', '.', '.', '2', '7', '5', '9', '.', '.'}
    };
    std::vector<std::vector<char>> expected = {
        {'5', '1', '9', '7', '4', '8', '6', '3', '2'},
        {'7', '8', '3', '6', '5', '2', '4', '1', '9'},
        {'4', '2', '6', '1', '3', '9', '8', '7', '5'},
        {'3', '5', '7', '9', '8', '6', '2', '4', '1'},
        {'2', '6', '4', '3', '1', '7', '5', '9', '8'},
        {'1', '9', '8', '5', '2', '4', '3', '6', '7'},
        {'9', '7', '5', '8', '6', '3', '1', '2', '4'},
        {'8', '3', '2', '4', '9', '1', '7', '5', '6'},
        {'6', '4', '1', '2', '7', '5', '9', '8', '3'}
    };
    // input
    for (auto i : board) {
        for (auto j : i)
            std::cout << " |" << j;
        std::cout << "|\n";
    }
    // my ans
    solution.solveSudoku(board);
    std::cout << "my ans:\n";
    for (auto i : board) {
        for (auto j : i)
            std::cout << " |" << j;
        std::cout << "|\n";
    }
    // ans
    std::cout << "ans:\n";
    for (auto i : expected) {
        for (auto j : i)
            std::cout << " |" << j;
        std::cout << "|\n";
    }
    return 0;
}