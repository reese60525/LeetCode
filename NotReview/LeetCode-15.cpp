/*
 * 題目：https://leetcode.com/problems/3sum/description/
 *
 * 題目解釋：
 * 給一組整數array，找出所有{num1, num2, nums}組合，此組合三個數相加等於0，且不重複index。
 * 當出現兩組{-1, 0, 1}、{-1, 0, 1}，而這兩組各自的index不同時，只取一組即可。
 *
 * 思路：
 * 遍歷nums，並在其中用two pointer找nums[i]+nums[l]+nums[r] = 0。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
        std::vector<std::vector<int>> res;

        // 排序nums，讓two pointer可以正常運作
        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++) {
            // 重複的nums[i]不要重複做
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            // 當nums[i] > 0時，nums[i] + nums[l] + nums[r]一定 > 0，所以不用繼續做
            if (nums[i] > 0) {
                break;
            }

            int l = i + 1, r = nums.size() - 1;
            while (l < r) {
                while (l < r && (nums[i] + nums[l] + nums[r] < 0)) {
                    ++l;
                }
                while (l < r && (nums[i] + nums[l] + nums[r] > 0)) {
                    --r;
                }
                if (l < r && nums[i] + nums[l] + nums[r] == 0) {
                    res.push_back({nums[i], nums[l], nums[r]});

                    // 重複的nums[l]不要重複做
                    do {
                        ++l;
                    }
                    while (l < nums.size() - 1 && nums[l] == nums[l - 1]);
                }
            }
        }
        return res;
    }
};

int main() {

    return 0;
}