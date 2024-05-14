/*
 * 題目: https://leetcode.com/problems/n-queens/
 * 題目解釋:
 * 思路:
 * 解法:
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    std::vector<std::vector<int>> check_repeat;
    std::vector<bool> ROWS, COLS, Diagonal1, Diagonal2;
    std::string printLn = "";
    int count = 0;
    // 公式:n, array[2n-1]  (x, y) 左上到右下:array[x+y], 左下到右上:array[(n-1)-(x-y)]

    bool checkRepeat(const std::vector<std::vector<std::string>> &res) {
        for (int i = 0; i < res.size(); ++i) {
            int count = 0;
            for (int j = 0; j < res[0].size(); ++j) {
                if (res[i][check_repeat[j][0]][check_repeat[j][1]] != 'Q') {
                    break;
                }
                ++count;
            }
            if (count == res[0].size()) {
                return false;
            }
        }
        return true;
    }

    void backTracking(int rank, int n, std::vector<std::vector<std::string>> &res) {
        if (rank == n && checkRepeat(res)) {
            ++count;
            std::vector<std::string> v;
            for (int i = 0; i < n; ++i) {
                std::string s = printLn;
                s[check_repeat[i][1]] = 'Q';
                v.emplace_back(s);
            }
            res.emplace_back(v);
            return;
        }

        for (int i = 0; i < n; ++i) {
            if (ROWS[i] == false) {
                for (int j = 0; j < n; ++j) {
                    if (COLS[j] == false) {
                        if (!Diagonal1[i + j] && !Diagonal2[(n - 1) - (i - j)]) {
                            check_repeat[rank][0] = i, check_repeat[rank][1] = j;
                            ROWS[i] = true, COLS[j] = true;
                            Diagonal1[i + j] = true, Diagonal2[(n - 1) - (i - j)] = true;

                            backTracking(rank + 1, n, res);

                            check_repeat[rank][0] = -1, check_repeat[rank][1] = -1;
                            ROWS[i] = false, COLS[j] = false;
                            Diagonal1[i + j] = false, Diagonal2[(n - 1) - (i - j)] = false;
                        }
                    }
                }
            }
        }
        return;
    }

    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::vector<std::string>> res;
        check_repeat.assign(n, std::vector<int>(2, -1));
        ROWS.assign(n, false);
        COLS.assign(n, false);
        Diagonal1.assign(2 * n - 1, false);
        Diagonal2.assign(2 * n - 1, false);

        for (int i = 0; i < n; ++i) {
            printLn += '.';
        }

        backTracking(0, n, res);
        std::cout << count << '\n';
        return res;
    }
};
int main() {
    Solution solution;
    solution.solveNQueens(2);
    return 0;
}