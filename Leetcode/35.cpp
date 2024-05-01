#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// TEST CASE
// 1 2 3 4 5 6 7 8 9 10 > 8
// begin = 0, end = 10, 6 < 8 => begin = (begin+end)/2
// begin = 5, end = 10, 8 == 8 => return 7
// 1 2 3 4 5 6 7 9 10 >　8
// begin = 0, end = 9, 5 < 8 => begin = (begin+end)/2
// begin = 4, end = 9, 7 < 8 => begin = (begin+end)/2
// begin = 6, end = 9, 9 > 8 => end = (begin+end)/2
// begin = 6, end = 7, end - begin == 1 => return nums[begin] > target ? begin : begin + 1
// 1 3 5 6 > 0
// begin =0, end = 4, 5 > 0 => end = (begin+end)/2
// begin = 0, end = 2, 3 > 0 => end = (begin+end)/2
// begin = 0, end = 1, end - begin == 1 => return nums[begin] > target ? begin : begin + 1
// 1 3 > 0
// begin = 0, end = 2, 3 > 0 => end = (begin+end)/2
// begin = 0, end = 1, end - begin == 1 => return nums[begin] > target ? begin : begin + 1

class Solution {
  public:
    int searchInsert(std::vector<int> &nums, int target) {
        int begin = 0, end = nums.size();
        while (true) {
            if (nums[(begin + end) / 2] == target)
                return (begin + end) / 2;
            if (end - begin == 1)
                return nums[begin] > target ? begin : begin + 1;
            else if (nums[(begin + end) / 2] < target)
                begin = (begin + end) / 2;
            else
                end = (begin + end) / 2;
        }
    }
};

int main() {
    Solution solution;
    std::vector<int> nums {1, 2, 3, 4, 5, 6, 7, 9, 10};
    int target = 8;
    std::cout << solution.searchInsert(nums, target) << '\n';
    return 0;
}