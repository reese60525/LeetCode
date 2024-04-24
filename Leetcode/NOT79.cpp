#include <iostream>
#include <string>
#include <vector>

using namespace std;

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// WA，思路也問題
void recursive_ans(vector<vector<char>> &board, string word, bool &ans, int x, int y) {
    if (board[x][y] != word[0]) {
        return;
    }
    word.erase(0, 1);
    board[x][y] = '~';
    if (word.length() == 0) {
        ans = true;
        return;
    }
    if (x - 1 >= 0)
        recursive_ans(board, word, ans, x - 1, y);
    if (x + 1 < board.size())
        recursive_ans(board, word, ans, x + 1, y);
    if (y - 1 >= 0)
        recursive_ans(board, word, ans, x, y - 1);
    if (y + 1 < board[0].size())
        recursive_ans(board, word, ans, x, y + 1);
}

bool exist(vector<vector<char>> &board, string word) {
    bool ans = false;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[0].size(); ++j) {
            recursive_ans(board, word, ans, i, j);
        }
    }
    return ans;
}

int main() {
    vector<vector<char>> input;
    string word;
    int i, j;
    cin >> i >> j >> word;
    while (i--) {
        vector<char> temp;
        for (int k = 0; k < j; ++k) {
            char a;
            cin >> a;
            temp.push_back(a);
        }
        input.push_back(temp);
    }
    // for (auto x : input) {
    //     for (auto y : x) {
    //         cout << y << " ";
    //     }
    //     cout << '\n';
    // }
    exist(input, word);
    return 0;
}