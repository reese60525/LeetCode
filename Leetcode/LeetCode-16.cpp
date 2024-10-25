/*
 * 題目：https://leetcode.com/problems/3sum-closest/description/
 *
 * 題目解釋：
 * 給一個整數array和target，找出array中三相異的數其相加的值最接近target。
 *
 * 思路：
 * 遍歷nums，內部用two pointer來找最接近的值。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int threeSumClosest(std::vector<int> &nums, int target) {
        int res = nums[0] + nums[1] + nums[2]; // 初始化res
        int dis = std::abs(res - target);      // res和target的距離

        // 排序nums讓two pointer能運作
        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); ++i) {
            // 重複的num[i]跳過
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            int l = i + 1, r = nums.size() - 1;
            while (l < r) {
                int cur = nums[i] + nums[l] + nums[r];
                int cur_dis = std::abs(cur - target);
                if (cur_dis <= dis) { // 判斷cur和target的距離是否比res和target的距離小
                    res = cur;        // 是的話就更新res和dis
                    dis = cur_dis;
                }

                if (cur < target) {
                    ++l;
                }
                else if (cur > target) {
                    --r;
                }
                else { // 如果cur == target，那res就是target，直接回傳
                    return target;
                }
            }
        }
        return res;
    }
};

int main() {

    return 0;
}