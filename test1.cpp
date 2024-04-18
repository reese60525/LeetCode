#include <iostream>
#include <string>
#include <vector>

using namespace std;

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

void recursive_ans(vector<vector<char>> board, string word, bool &ans, int x, int y, char from) {
    if (board[x][y] != word[0]) {
        return;
    }
    cout << "1from=" << from << ", x=" << x << ", y=" << y << ", word=" << word
         << ", board[x][y]= " << board[x][y] << '\n';
    word.erase(0, 1);
    board[x][y] = '~';
    if (word.length() == 0) {
        ans = true;
        return;
    }
    cout << "2from=" << from << ", x=" << x << ", y=" << y << ", word=" << word
         << ", board[x][y]= " << board[x][y] << '\n';
    if (x - 1 >= 0 && from != 'u')
        recursive_ans(board, word, ans, x - 1, y, 'd');
    X if (x + 1 < board.size() && from != 'd') recursive_ans(board, word, ans, x + 1, y, 'u');
    if (y - 1 >= 0 && from != 'l')
        recursive_ans(board, word, ans, x, y - 1, 'r');
    if (y + 1 < board[0].size() && from != 'r')
        recursive_ans(board, word, ans, x, y + 1, 'l');
}

bool exist(vector<vector<char>> &board, string word) {
    bool ans = false;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[0].size(); ++j) {
            recursive_ans(board, word, ans, i, j, 'x');
        }
    }
    cout << "ans=" << ans << '\n';
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
