/*
 *  Author      : Reese
 *  Created On  : 2025-01-20 09:18
 *  Description : https://leetcode.com/problems/first-completely-painted-row-or-column/description/
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
    int firstCompleteIndex(std::vector<int> &arr, std::vector<std::vector<int>> &mat) {
        int r = mat.size(), c = mat[0].size();
        // row 和 col 用於記錄每行每列有幾個 element 被走訪過
        int row[r], col[c];
        std::memset(row, 0, sizeof(row));
        std::memset(col, 0, sizeof(col));
        // pos[i] 表示 i 在 mat 中的 index
        int pos[r * c + 1];
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                int n = mat[i][j];
                pos[n] = i * c + j;
            }
        }

        // 遍歷 arr，將遇到的 element 所對應的 row 和 col 的值 - 1
        for (int i = 0; i < arr.size(); ++i) {
            int x = pos[arr[i]] / c, y = pos[arr[i]] % c;
            ++row[x], ++col[y];
            if (row[x] == c || col[y] == r) {
                return i;
            }
        }

        return -1;
    }
};

int main() {

    return 0;
}