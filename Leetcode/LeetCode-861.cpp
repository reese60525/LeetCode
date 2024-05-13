/*
 * 題目: https://leetcode.com/problems/score-after-flipping-matrix/description/
 *
 * 題目解釋:
 * 給一個matrix，每個row都視為一個binary num，可以做反轉整個row或整個column的0和1，請求出
 * 任意次反轉後(可以0次反轉)的每個row(binary num)相加最大值。
 * EX:
 * 0, 0, 1, 1    1, 1, 1, 1
 * 1, 0 ,1, 0 => 1, 0, 0, 1
 * 1, 1, 0, 0    1, 1, 1, 1
 * 左邊是題目給的，右邊是最終反轉結果，sum看每個row: sum = 0x1111 + 0x1001 + 0x1111 = 39。
 *
 * 思路:
 * 對於一個binary num，開頭的bit為1是最大，舉個例子，0x1000 = 8, 0x0111 = 7，所以先確認每個row
 * 的開頭是否為1，不是的話就反轉整個row，再來看每個column，由於bit大小相同(都是2^n)，所以1的數量越
 * 多越好，若該column的0數量大於1，則反轉整個column即可。
 *
 * 解法:
 * 用for迴圈做上面的思路。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    int matrixScore(std::vector<std::vector<int>> &grid) {
        int sum = 0, bit = 1;
        // 確認每個row的開頭是0還是1，0的話就反轉整個row，1不變動
        for (int i = 0; i < grid.size(); ++i) {
            if (grid[i][0] == 0) {
                for (int j = 0; j < grid[0].size(); ++j) {
                    grid[i][j] = 1 - grid[i][j];
                }
            }
        }
        // 先計算每個column的0和1總數，若0的數量 > 1則翻轉整個column
        // 順便計算sum
        for (int i = grid[0].size() - 1; i > -1; --i) {
            int count[2] = {0, 0};
            // 計算column的0和1數量
            for (int j = 0; j < grid.size(); ++j) {
                if (grid[j][i] == 0) {
                    ++count[0];
                }
                else {
                    ++count[1];
                }
            }
            // 0的數量>1的數量，此時反轉整個column能得到更大的值
            // 不必去修改grid，直接計算sum就好，節省時間
            if (count[0] > count[1]) {
                count[1] = count[0]; // 0和1數量對調
            }
            sum += count[1] * bit;
            bit <<= 1; // bit表示 2^0 => 2^1 => 2^2 ...
        }
        return sum;
    }
};
int main() { return 0; }