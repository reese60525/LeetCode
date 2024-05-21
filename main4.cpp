/*
 * 題目:
 * 題目解釋:
 * 思路:
 * 解法:
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<std::vector<int>> res;
    std::vector<std::vector<int>> subsets(std::vector<int> &nums) {
        std::vector<int> temp;

        backTracking(0, temp, nums);
        return res;
    }

  private:
    void backTracking(int index, std::vector<int> &cur, std::vector<int> &nums) {
        if (index == nums.size()) {
            res.emplace_back(cur);
            return;
        }

        cur.emplace_back(nums[index]);
        backTracking(index + 1, cur, nums);
        cur.pop_back();
        backTracking(index + 1, cur, nums);
    }
};

int main() {
    return 0;
}
