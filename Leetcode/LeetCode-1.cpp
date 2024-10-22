/*
 * 題目: https://leetcode.com/problems/two-sum/description/
 *
 * 題目解釋:
 * 給一組不重複的正整數vector和一個target，找出能vector中兩個數相加等於target並且return
 * 兩數的index。
 *
 * 思路:
 * 使用unordered_map來記錄每個數的index，並且利用target-nums[i]來找尋另一個數是否存在於
 * vector中。
 */
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
        std::unordered_map<int, int> table;

        for (int i = 0; i < nums.size(); ++i) {
            // 查找另一個數是否存在於table中，若存在則找到兩數相加等於target
            if (table.find(target - nums[i]) != table.end()) {
                return {table[target - nums[i]], i};
            }

            table[nums[i]] = i; // 將nums[i]之index存入table中
        }

        return {-1, -1}; // 因為必定洽有一組解，所以這行不會用到，只是為了過編譯
    }
};

int main() {

    return 0;
}