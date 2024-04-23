#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
// two pointer，解法和leetcode 15相似
int threeSumClosest(std::vector<int> &nums, int target) {
    int l, r, n = nums.size(), ans = nums[0] + nums[1] + nums[2];
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n; ++i) {
        l = i + 1;
        r = n - 1;
        while (l < r) {
            int sum = nums[i] + nums[l] + nums[r];
            if (abs(target - ans) > abs(target - sum)) {
                ans = sum;
            }
            if (ans == target) {
                return ans;
            }
            else if (sum < target) {
                ++l;
            }
            else if (sum > target) {
                --r;
            }
        }
    }
    return ans;
}
int main() {
    //-1, -4, 0, 1, 2, 2, 2, -1, -4, 3
    std::vector<int> input = {-1000, -5, -5, -5, -5, -5, -5, -1, -1, -1};
    int target;
    std::cin >> target;
    std::cout << threeSumClosest(input, target);
    return 0;
}