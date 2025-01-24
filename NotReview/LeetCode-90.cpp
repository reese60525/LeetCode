/*
 * 題目: https://leetcode.com/problems/subsets-ii/
 *
 * 題目解釋:
 * 給一個有重複數字的nums array，求所有的不重複subset。EX:{1,2,2}的subset有{}、{1}、{2}、{1, 2}、{2, 2}
 * 、{1, 2, 2}。
 *
 * 思路:
 * 使用backtracking algorithm。
 *
 * 解法:
 * 換LeetCode-78非常相似，只差在這題的nums有重複數字，因此要改變backtracking function的判斷方式。
 * 方法1:
 * 先對nums做排序，方便等等在backtracking中的判斷，用在backtracking中用for迴圈遍歷nums，如果在目前的level中，
 * for迴圈內目前的num和上個nums相同，則需要跳過以避免重複組合，至於迴圈中的backtracking()呼叫一次就好，因為當後
 * 面的backtracking執行完回到目前的level後，會對arr執行pop_back()的動作，然後for迴圈進到下階段，接著再進行一次
 * backtracking()，此行為就等同於no pick的backtracking()，假設我現在arr = {1, 3, 4}，push一個5變成{1, 3, 4, 5}，
 * 接著進入下一level的backtracking()，回來後會把5給pop，arr = {1, 3, 4}，接著進入下階段for迴圈，此時假設當前
 * nums[i]是6，重複上階段for迴圈做的事情，push 6進arr，arr = {1, 3, 4, 6}，然後再去呼叫backtracking()進到
 * 下個level，可以發現for迴圈已經實現了no pick的功能，沒必要再pick後再呼叫一次no pick的backtracking()。
 * 方法2:
 * 判斷如果上個level是選擇no pick的話，那麼如果現在level的num和上個level的num相同，則必須終止目
 * level以避免重複組合。
 */
#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 方法1
class Solution {
  public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums) {
        std::vector<std::vector<int>> res;
        std::vector<int> arr;

        std::sort(nums.begin(), nums.end()); // 先對nums排序，方便之後在backtracking function的處理。
        backTracking(0, arr, nums, res);
        return res;
    }

  private:
    void backTracking(int index, std::vector<int> &arr, std::vector<int> &nums, std::vector<std::vector<int>> &res) {
        res.push_back(arr);

        for (int i = index; i < nums.size(); ++i) {
            // 用來避免重複組合的判斷，若是當前的index是第一次使用，則不會跳過
            // 若是當前index不是進來這個遞迴時的index(也就是非開頭)，而且目前num跟上個nums相同則要跳過
            if (i > index && nums[i] == nums[i - 1]) {
                continue;
            }
            // 不需要再一個"沒選擇當前num"的backtracking()，因為這是在for迴圈中遍歷
            // 進到下一次迴圈時就達成了no pick的動作
            arr.push_back(nums[i]);
            backTracking(i + 1, arr, nums, res);
            arr.pop_back();
        }
    }
};

// // 方法2
// class Solution {
//   public:
//     std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums) {
//         std::vector<int> arr;
//         std::vector<std::vector<int>> res;

//         std::sort(nums.begin(), nums.end());
//         backTracking(0, true, arr, nums, res);
//         return res;
//     }

//   private:
//     void backTracking(int index, bool is_pick, std::vector<int> &arr, std::vector<int> &nums,
//                       std::vector<std::vector<int>> &res) {
//         if (index == nums.size()) {
//             res.push_back(arr);
//             return;
//         }

//         // no pick
//         backTracking(index + 1, false, arr, nums, res);
//         // 若目前的num和上個level的num相同，並且在上一level就已經決定no pick
//         // 那麼在這level也不該pick，必須剪枝
//         if (index > 0 && nums[index] == nums[index - 1] && !is_pick) {
//             return;
//         }
//         arr.push_back(nums[index]);
//         backTracking(index + 1, true, arr, nums, res);
//         arr.pop_back();
//     }
// };

int main() {

    return 0;
}