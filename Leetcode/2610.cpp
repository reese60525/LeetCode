#include <algorithm>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<std::vector<int>> findMatrix(std::vector<int> &nums) {
        std::vector<std::vector<int>> ans;

        sort(nums.begin(), nums.end());

        while (nums.size() > 0) {
            int temp_num = -2000;
            std::vector<int> temp_vector;
            for (int i = 0; i < nums.size();) {
                if (temp_num == nums[i]) {
                    ++i;
                    continue;
                }
                temp_num = nums[i];
                nums.erase(nums.begin() + i);
                temp_vector.push_back(temp_num);
            }
            ans.push_back(temp_vector);
        }

        return ans;
    }
};

int main() {
    Solution solution;
    std::vector<int> nums = {1, 3, 4, 1, 2, 3, 1};
    solution.findMatrix(nums);
    return 0;
}