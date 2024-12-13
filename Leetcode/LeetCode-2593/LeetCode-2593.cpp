/*
 * 題目：
 *
 * 題目解釋：
 *
 * 思路：
 *
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    long long findScore(std::vector<int> &nums) {
        int n = nums.size();
        long long res = 0;

        for (int right = 0; right < n; right += 2) {
            // 當前遞減區間的起始 index
            int left = right;
            // 尋找遞減區間的結尾 index
            while (right < n - 1 && nums[right] > nums[right + 1]) {
                ++right;
            }
            // 往左遍歷區間進行累加
            for (int cur = right; cur >= left; cur -= 2) {
                res += nums[cur];
            }
        }

        return res;
    }
};

int main() {

    return 0;
}