#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<bool> isArraySpecial(std::vector<int> &nums, std::vector<std::vector<int>> &queries) {
        int n = nums.size(), k = 0; // k 表示當前共有幾組 special subarray
        int prev = ~(nums[0] & 1); // prev 表示前一個數字是奇數還是偶數，初始化為 nums[0] 的奇偶數的相反

        // 遍歷 nums 計算每個數字目前遇到的 special subarray 數量，並將結果存儲在 nums 中
        for (int &num : nums) {
            k += prev == (num & 1); // 如果當前數字和前一個數字奇偶性相同，則 k 加 1
            prev = num & 1;         // 更新 prev 為當前數字的奇偶性
            num = k;                // 將 num 設為count，表示該數是屬於第 k 組的 special subarray
        }

        // 查詢兩個數之間的 subarray 是否為 special subarray
        // 若兩數都屬於同一組則這兩數能形成 special subarray
        int i = 0;
        std::vector<bool> res(queries.size());
        for (std::vector<int> &query : queries) {
            res[i++] = nums[query[0]] == nums[query[1]];
        }

        return res;
    }
};

int main() {

    return 0;
}