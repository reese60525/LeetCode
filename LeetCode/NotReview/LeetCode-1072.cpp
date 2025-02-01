/*
 * 題目： https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/description/
 *
 * 題目解釋：
 * 給一個由0和1組成的matrix，可以翻轉任何column，求翻轉column(也可以不翻轉)後，row的值全為0或1
 * 的row數量之最大值。
 * e.g.
 * 0 0 0                   1 1 0
 * 0 0 1  對col{0,1}翻轉 => 1 1 1  ，row{1,2}的值全為0或1，res = 2。
 * 1 1 0                   0 0 0
 *
 * 思路：
 * 首先將row兩兩比對並觀察，可以發現上面例子中的{0, 0, 1}和{1, 1, 0}可以透過翻轉將其變成全為0或1，
 * 如果我們對一個row其將相臨且相同的數字進行分組，可以發現這兩個row的pattern都是**|*，相鄰的*可以同
 * 為0或1，而由|分開的則表示兩邊的*為相反值，比如說pattern: ***|*|****|** 可以是1110111100或是
 * 0001000011，而這兩種都能翻轉部分col使其row全為0或1，因此可以將計算matrix的每個row的對應pattern
 * 出現次數，某個pattern出現最多次的即為答案。
 * 那如何將row轉換成pattern呢？創建一個bool array其初始值全為0，然後觀察1110111100這個row，已row[0]
 * 也就是1為該row的分組基準，遍歷row，如果值和row[0]不同則將bool array相對應的位置的value改為1，這麼
 *　一來可以得到一個pattern:0001000011(***|*|****|**)，如果現在有另一個row:0001000011，按照上面的
 * 操作可以得到一樣的pattern:0001000011(***|*|****|**)，因此可以將每個row轉換成pattern，最後再計算
 * 出現最多次pattern的次數即可。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int maxEqualRowsAfterFlips(std::vector<std::vector<int>> &matrix) {
        int res = 0, m = matrix.size(), n = matrix[0].size();
        std::unordered_map<std::bitset<300>, int> freq; // 計算每個pattern出現次數

        for (auto &row : matrix) {
            std::bitset<300> key;         // bool array，size=300(題目給的matrix column最大值)
            for (int i = 1; i < n; ++i) { // 將row轉換成pattern
                if (row[0] != row[i]) {
                    key[i] = true;
                }
            }
            freq[key]++;                    // 累加該pattern出現次數
            res = std::max(res, freq[key]); // 更新pattern出現次數最大值
        }

        return res;
    }
};

int main() {

    return 0;
}