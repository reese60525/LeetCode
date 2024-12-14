/*
 * 題目：
 *
 * 題目解釋：
 *
 * 思路：
 *
 */
#include <iostream>
#include <map>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    long long continuousSubarrays(std::vector<int> &nums) {
        size_t l = 0, r = 0, n = nums.size(); // l 和 r 為當前 window 的範圍
        long long res = 0;
        std::map<int, int> window; // 用於儲存 window 中所有 element 的出現次數，最多只會有四個 element

        for (; r < n; ++r) {
            ++window[nums[r]];
            // begin() 為 map 第一個 element 也是最小值，rbegin() 為 map 的最後一個 element 也是最大值
            while (window.rbegin()->first - window.begin()->first > 2) {
                // 將 window 往右縮小，最左邊的 element 次數減 1
                --window[nums[l]];
                // 如果 element 的出現次數為 0，將其從 map 中刪除以維護最大最小值
                if (window[nums[l]] == 0) {
                    window.erase(nums[l]);
                }
                ++l;
            }
            // 累加當前 subarray 的長度
            res += r - l + 1;
        }

        return res;
    }
};

int main() {

    return 0;
}