/*
 * 題目: https://leetcode.com/problems/path-with-maximum-gold/description/

 * 題目解釋:
 * 給一個m * n的matrix，每個走訪過的格子都不能重複走，不能走到值為0的格子，求能夠走訪最大值
 * EX:
 * [1,0,7]  grid[0][0](1)可以往下走到grid[1][0](2)，但是不能往上或往左，因為超出範圍，
 * [2,0,6]  也不可以往右，因為值為0，走到grid[1][0](2)之後不能回頭走到grid[0][0](1)，只
 * [3,4,5]  能往下走到grid[2][0](3)。
 * [0,3,0]
 * [9,0,20]

 * 思路:
 * 第一次直覺是dfs+dp，但是dp是不可行的，和LeetCode第79題一樣，因為使用dp時每個狀態之間要有關
 * 聯性，並且要有重複的子問題，但是這題每一個狀態和其他狀態是沒有關聯的，所以不能用dp解決這問題。
 * 考慮到測資有說grid最大為15*15，而且最重要的是非0的金礦點小於等於25，這讓使用backtracking +
 * dfs的解法可行。

 * 解法:
 * 可以遍歷grid讓每個grid[][]為起始點進行dfs走訪，使用backtracking algorithm時可以想想要怎
 * 麼來優化整體速度，在這邊我用兩個方式來優化，一個是計算grid中所有的金礦總量，當dfs走訪時res等於
 * totalGold，不可能再得到更多金礦，因此可以提早結束程式，第二個則是確認grid中是否所有金礦都非0，
 * 是的話代表grid所有點都能走訪，因此res即為totalGold。
 * 時間複雜度:O(v * 3^v)，v是非0的礦點數量，3的指數代表dfs中3個方向能選擇。
 * 空間複雜度:O(m * n)，m是grid的row，n是grid的col。
 *
 * 小抱怨一下，這題早上八點開始想，大概一個小時後確定不能dp，原本已經寫出backtracking algorithm
 * 了，但是!但是竟然TLE，然後我又跑去想dp的可能性，最後受不了在下午看解答，解果發現我原本的思路根本
 * 沒問題，那為什麼會TLE?後來才發現我dfs function因為偷懶不想要每次還要自己恢復走訪過的值(走訪過的
 * 點我都會設為0來表示走訪過)，所以我pass進dfs的grid是call by value而不是call by reference，
 * 導致每次call dfs都要複製一個新的grid，讓時間和空間雙雙炸開= =，所以才導致TLE，吐了都。
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
    // grid中所有的gold數量，grid的row and col
    int totalGold, ROWS, COLS;
    // 用來計算往哪個方向搜尋
    int direction[4][2] = {
        {-1, 0 },
        {1,  0 },
        {0,  -1},
        {0,  1 }
    };
    // 計算totalGold和grid是否全非0
    bool isAllNoneZero(auto &grid) {
        bool none_zero = true;
        for (auto i : grid) {
            for (auto j : i) {
                totalGold += j;
                if (j == 0) {
                    none_zero = false;
                }
            }
        }
        return none_zero;
    }
    // dfs走訪所以可能
    int dfs(int row, int col, auto &grid) { // grid要call by reference才不會TLE
        // 邊界條件，以及grid[][]=0的話代表沒金礦或是已經走訪過
        if (row == ROWS || row < 0 || col == COLS || col < 0 || grid[row][col] == 0) {
            return 0;
        }

        int res = 0, cur_gold = grid[row][col];
        grid[row][col] = 0; // 把目前位置金礦設定為0，表示走訪過

        for (auto dir : direction) {
            res = std::max(res, dfs(row + dir[0], col + dir[1], grid)); // 搜索四個方向的最大金礦數量
            if (res == totalGold) { // 金礦數量 = grid中所有金礦數量，不可能再更多，直接結束dfs
                return totalGold;
            }
        }
        grid[row][col] = cur_gold; // 恢復原本金礦數量

        return res + cur_gold; // 目前金礦數量+四個方向搜索到的最大值
    }

    int getMaximumGold(std::vector<std::vector<int>> &grid) {
        int res = 0;
        totalGold = 0, ROWS = grid.size(), COLS = grid[0].size();

        if (isAllNoneZero(grid)) { // grid中如果全非0，直接輸出全部金礦加總
            return totalGold;
        }

        for (int i = 0; i < ROWS; ++i) { // 把每個grid[][]當起始點去做dfs走訪
            for (int j = 0; j < COLS; ++j) {
                res = std::max(res, dfs(i, j, grid));
                if (res == totalGold) { // 金礦數量 = grid中所有金礦數量，不可能再更多，直接結束dfs
                    return totalGold;
                }
            }
        }

        return res;
    }
};
// DATA TEST
// {1,0,7},{2,0,6},{3,4,5},{0,3,0},{9,0,20}
// {0,6,0},{5,8,7},{0,9,0}
// {1,0,7,0,0,0},{2,0,6,0,1,0},{3,5,6,7,4,2},{4,3,1,0,2,0},{3,0,5,0,20,0}
int main() {
    Solution solution;
    std::vector<std::vector<int>> grid {
        {1, 0, 7, 0, 0,  0},
        {2, 0, 6, 0, 1,  0},
        {3, 5, 6, 7, 4,  2},
        {4, 3, 1, 0, 2,  0},
        {3, 0, 5, 0, 20, 0}
    };
    std::cout << solution.getMaximumGold(grid);
    return 0;
}
