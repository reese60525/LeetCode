/*
 * 題目: https://leetcode.com/problems/next-permutation/description/
 *
 * 題目解釋:
 * 給定一組數組(數字可重複)，找出其下一個排列組合。
 * EX:(1, 2, 3) -> (1, 3, 2) -> (2, 1, 3) -> (2, 3, 1) -> (3, 1, 2) -> (3, 2, 1)。
 *
 * 思路:
 * 可以發現數組是逐漸變大的，因此要求下一個數組排列，要以"最小幅度"變大的數組，將index從數組尾段開始，
 * 去比較當前的num是否比右邊的(當前index-1)nums小，是的話就表示當前的num在右側必有一個num比他大，交
 * 換比他大的num之中最小的num即可達成"最小幅度"的變大，在把當前num右側的nums由小排到大就行了。
 * EX:(1, 3, 7, 6, 9, 8, 7, 1)，從右邊開始看，1右邊沒人可比，7比1大跳過，8比7大跳過，9比8大跳過，
 * 6比9小，找到(6, 9, 8, 7, 1)這數組還能再變大，像是(9, 8, 7, 1)就已經是最大了無法再變大，此時再找
 * 出比6大的所有數，選其中最小的來進行交換，也就是從(9, 8, 7)選最小的7來和6交換，會變成(7, 9, 8, 6, 1)
 * 由於交換前，6右邊的nums已經是遞減排序了，所以6和比他大的數字7交換後，仍然呈現遞減排序，此時再將(9, 8, 6, 1)
 * reverse，即可得到(7, 1, 6, 8, 9)這組數，也就是要找的"最小增幅"，最後答案為(1, 3, 7, 7, 1, 6, 8, 9)。
 *
 * 解法1:
 * 從nums.size()-2開始找右邊所有比他大的數，再找出這之間最小的數，找到後swap再將剩下的數sort。
 * 解法2:
 * 從nums.size()-2開始找右邊比他大的數，利用右邊的數會呈現遞減排序的特性，只要確認cur_num的右邊num
 * 是否比cur_num大，是的話再從最尾端開始找比cur_num大的數，一樣利用遞減排序的特性，當找到比cur_num的num
 * 也代表是比cur_num大的nums之中最小的num。
 */
#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 解法2
class Solution {
  public:
    void nextPermutation(std::vector<int> &nums) {
        int index;
        // 找出可以再變更大的數組節點
        for (int i = nums.size() - 2; i > -1; --i) {
            if (nums[i] < nums[i + 1]) {
                index = i;
                break;
            }
        }
        // 代表nums是最後的排序數組，EX:(3, 2, 1)
        if (index == -1) {
            reverse(nums.begin() + index + 1, nums.end());
            return;
        }
        // 找出能跟該節點交換的num
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
// // 解法1
// class Solution {
//   public:
//     bool swapNums(int index, std::vector<int> &nums) {
//         int min = 0x3f3f3f3f, min_index, target = nums[index];
//         for (int i = index + 1; i < nums.size(); ++i) {
//             if (target < nums[i] && nums[i] < min) {
//                 min = nums[i];
//                 min_index = i;
//             }
//         }
//         if (min == 0x3f3f3f3f)
//             return false;
//         else {
//             int temp = nums[index];
//             nums[index] = min;
//             nums[min_index] = temp;
//             return true;
//         }
//     }

//     void nextPermutation(std::vector<int> &nums) {
//         for (int i = nums.size() - 2; i > -1; --i) {
//             if (swapNums(i, nums)) {
//                 sort(nums.begin() + i + 1, nums.end());
//                 return;
//             }
//         }
//         sort(nums.begin(), nums.end());
//     }
// };
int main() { return 0; }