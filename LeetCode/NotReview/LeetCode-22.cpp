/*
 * 題目： https://leetcode.com/problems/generate-parentheses/description/
 *
 * 題目解釋：
 * 給一個數字n，找出所有strings，這些string由n組左右括號排列組成一個valid括號string。
 * e.g. n = 1，strings = {"()"}。 n = 2，strings = {"()()", "(())"}。
 *
 * 思路：
 * 用backtracking algorithm，每次只添加一個 '(' 或 ')' 到string，並且用兩個整數l和r
 * 來記錄當前左右括號的數量，當(l < r || l > n || r > n)時表示當前string not valid，
 * 若(l == n && r === n)表示當前string valid，將其加入res。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<std::string> generateParenthesis(int n) {
        int l = 0, r = 0;
        std::string s;
        std::vector<std::string> res;

        backTracking(res, s, n, 0, 0);

        return res;
    }

  private:
    void backTracking(std::vector<std::string> &res, std::string &s, int &n, int l, int r) {
        if (l < r || l > n || r > n) { // not valid
            return;
        }

        if (l == n && r == n) { // valid string
            res.push_back(s);
            return;
        }

        // 進入下一層backtracking
        s += '(';
        backTracking(res, s, n, l + 1, r);
        s.pop_back();

        s += ')';
        backTracking(res, s, n, l, r + 1);
        s.pop_back();
    }
};

int main() {

    return 0;
}