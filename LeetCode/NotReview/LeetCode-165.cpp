/*
 * 解法:
 * 把version1和version2各自的value存到vector中，再去做比較。
 * EX:version1 = 1.02.12, version2 = 1.002.122.2
 * nums[0] = {1, 2, 12}, nums[1] = {1, 2, 122, 2}
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    // 用來build version_string的nums
    void build_nums(std::string &version, std::vector<int> &nums) {
        bool check = false;
        int num = 0;
        for (char i : version) {
            if (i == '.') {
                nums.emplace_back(num);
                check = false;
                num = 0;
            }
            else if (i != '0' && !check) {
                check = true;
            }
            if (check) {
                num *= 10;
                num += (i - '0');
            }
        }
        nums.emplace_back(num); // 處理最後一個num
    }
    // 不想寫在compareVersion中，因為要根據size不同要寫兩次一樣的內容= =
    // x代表return值，假設nums1是nums[0]，則x = 1，反之x = -1。
    int compare(std::vector<int> nums1, std::vector<int> nums2, int x) {
        for (int i = 0; i < nums1.size(); ++i) {
            if (nums1[i] > nums2[i])
                return x;
            else if (nums1[i] < nums2[i])
                return -x;
        }
        for (int i = nums1.size(); i < nums2.size(); ++i) {
            if (nums2[i] != 0)
                return -x;
        }
        return 0;
    }
    int compareVersion(std::string version1, std::string version2) {
        std::vector<int> nums[2];
        build_nums(version1, nums[0]);
        build_nums(version2, nums[1]);
        if (nums[0].size() < nums[1].size())
            return compare(nums[0], nums[1], 1);
        else
            return compare(nums[1], nums[0], -1);
    }
};
int main() { return 0; }