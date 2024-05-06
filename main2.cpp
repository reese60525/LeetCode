#include <algorithm>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
bool fun(int sum, int index, int target, std::vector<int> nums) {
    std::cout << "sum:" << sum << " ,index:" << index << ", nums[index]:" << nums[index] << '\n';
    if (index >= nums.size() || (sum + nums[index] > target))
        return false;
    if (sum + nums[index] == target) {
        std::cout << nums[index] << '\n';
        return true;
    }
    if (fun(sum + nums[index], index + 1, target, nums) || fun(sum, index + 1, target, nums)) {
        std::cout << nums[index] << '\n';
        return true;
    }
    return false;
}
int main() {
    std::vector<int> nums {18, 17, 18, 11, 15, 4, 13, 11, 9}; // 4,9,13,15,17 (58)
    sort(nums.begin(), nums.end());
    std::cout << "ans:" << fun(0, 0, 58, nums);
    return 0;
}