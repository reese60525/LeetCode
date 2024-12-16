/*
 * 題目：
 *
 * 題目解釋：
 *
 * 思路：
 *
 */
#include <cstddef>
#include <iostream>
#include <queue>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<int> getFinalState(std::vector<int> &nums, int k, int multiplier) {
        // 建立 min heap pq
        auto cmp = [&](size_t &a, size_t b) {
            return (nums[a] == nums[b]) ? a > b : nums[a] > nums[b];
        };
        std::priority_queue<size_t, std::vector<size_t>, decltype(cmp)> pq(cmp);
        for (size_t i = 0; i < nums.size(); ++i) {
            pq.push(i);
        }

        // 進行 k 次操作
        while (k--) {
            size_t idx = pq.top();
            pq.pop();
            nums[idx] *= multiplier;
            pq.push(idx);
        }

        return nums;
    }
};

int main() {

    return 0;
}