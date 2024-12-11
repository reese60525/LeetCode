#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int maximumBeauty(std::vector<int> &nums, int k) {
        int max_num = *std::max_element(nums.begin(), nums.end());
        std::vector<int> cnt(max_num + 2); // cnt[max_num + 1] 用於處理邊界條件

        for (int num : nums) {
            // nums[i] 可變換的範圍為 [nums[i] - k, nums[i] + k]
            // 出現頻率增加的起始位置為 nums[i] - k，出現頻率下降的位置為 nums[i] + k + 1
            ++cnt[std::max(num - k, 0)];
            --cnt[std::min(num + k + 1, max_num + 1)];
        }

        // 計算 prefix sum 即可得到每個 element 的出現頻率，最大值為答案
        int res = 0, count = 0;
        for (int c : cnt) {
            count += c;
            res = std::max(res, count);
        }

        return res;
    }
};

int main() {

    return 0;
}