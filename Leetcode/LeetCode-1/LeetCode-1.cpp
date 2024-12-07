#include <iostream>
#include <unordered_map>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<int> twoSum(std::vector<int> &nums, int target) {
        std::unordered_map<int, int> table; // {value, index}

        for (int i = 0; i < nums.size(); ++i) {
            // 查找另一個數是否存在於 table 中
            if (table.find(target - nums[i]) != table.end()) {
                return {i, table[target - nums[i]]};
            }

            table[nums[i]] = i; // 將 nums[i] 的 index 存入 table 中
        }

        // 因為必定洽有一組解，所以這行不會用到，只是為了過編譯
        return {-1, -1};
    }
};

int main() {

    return 0;
}