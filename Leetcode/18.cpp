/*
 * 解法:
 * 和LeetCode第15題3sum的思路是一模一樣，用兩個for迴圈i、j代表兩個數字，再用while跑
 * two pointer找另外兩個數字。
 */
#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target) {
        std::vector<std::vector<int>> ans;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < signed(nums.size()) - 3; ++i) { // 要用signed的型態，不然遇到nums不到3個都會變成負數，會出錯
            if (i > 0 && nums[i] == nums[i - 1])            // 重複做過的跳過
                continue;
            long long check1 = nums[i] + static_cast<long long>(nums[nums.size() - 1]) * 3;
            long long check2 = nums[i] + static_cast<long long>(nums[i + 1]) * 3;
            if (check1 < target || check2 > target) // 超出範圍的就不用再進for(j)浪費時間
                continue;

            for (int j = i + 1; j < signed(nums.size()) - 2; ++j) { // 要用signed的型態，不然遇到nums不到2個都會變成負數，會出錯
                if (j > i + 1 && nums[j] == nums[j - 1])            // 重複做過的跳過
                    continue;
                check1 = static_cast<long long>(nums[i]) + nums[j] + nums[nums.size() - 1] * 2;
                check2 = static_cast<long long>(nums[i]) + nums[j] + nums[j + 1] * 2;
                if (check1 < target || check2 > target) // 超出範圍的就不用再進while浪費時間
                    continue;

                int left = j + 1, right = nums.size() - 1;
                while (left < right) {
                    // 先把右式其中一個nums轉成long long type，這樣相加時才不會overflow
                    long long sum = static_cast<long long>(nums[i]) + nums[right] + nums[j] + nums[left];
                    if (sum == target) {
                        ans.emplace_back(std::vector {nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) { // 重複做過的跳過
                            ++left;
                        }
                        while (left < right && nums[right] == nums[right - 1]) { // 重複做過的跳過
                            --right;
                        }
                        ++left;
                        --right;
                    }
                    else if (sum < target) {
                        ++left;
                    }
                    else {
                        --right;
                    }
                }
            }
        }
        return ans;
    }
};
int main() { return 0; }