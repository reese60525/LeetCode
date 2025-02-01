/*
 * 題目： https://leetcode.com/problems/next-permutation/description/
 *
 * 題目解釋：
 * 給定一組數組(數字可重複)，找出其下一個排列組合。
 * EX:(1, 2, 3) -> (1, 3, 2) -> (2, 1, 3) -> (2, 3, 1) -> (3, 1, 2) -> (3, 2, 1)。
 *
 * 思路：
 * 可以發現數組是逐漸變大的，因此要求下一個數組排列，要以"最小幅度"變大的數組，將 index 從數組尾段開始，
 * 去比較當前的 num 是否比右邊的(當前 index-1) nums 小，是的話就表示當前的num在右側必有一個 num 比他大，交
 * 換比他大的 num 之中最小的 num 即可達成"最小幅度"的變大，再把當前 num 右側的 nums 由小排到大就行了。
 * e.g.：(1, 3, 7, 6, 9, 8, 7, 1)，從右邊開始看，1 右邊沒人可比，7 比 1 大跳過，8 比 7 大跳過，9 比 8 大跳過，
 * 6 比 9 小，找到(6, 9, 8, 7, 1)這數組還能再變大，像是(9, 8, 7, 1)就已經是最大了無法再變大，此時再找
 * 出比 6 大的所有數，選其中最小的來進行交換，也就是從(9, 8, 7)選最小的 7 來和 6 交換，會變成(7, 9, 8, 6, 1)，
 * 由於交換前，6 右邊的 nums 已經是遞減排序了，所以 6 和比他大的 7 交換後，仍然呈現遞減排序，此時再將(9, 8, 6, 1)
 * reverse，即可得到(7, 1, 6, 8, 9)這組數，也就是要找的"最小增幅"，最後答案為(1, 3, 7, 7, 1, 6, 8, 9)。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    void nextPermutation(std::vector<int> &nums) {
        // 找出可以再變更大的數組節點
        int index;
        for (int i = nums.size() - 2; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) {
                index = i;
                break;
            }
        }

        // index = -1 代表 nums 是最後的排序數組，e.g. nums = {3, 2, 1}
        if (index == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }

        // 找出能跟該節點交換的 num
        for (int i = nums.size() - 1; i > index; --i) {
            if (nums[i] > nums[index]) {
                std::swap(nums[i], nums[index]);
                break;
            }
        }

        // reverse節點右邊的nums
        reverse(nums.begin() + index + 1, nums.end());
    }
};

int main() {

    return 0;
}