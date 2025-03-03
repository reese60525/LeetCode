/*
 *  Author      : Reese
 *  Created On  : 2025-02-26 08:33
 *  Description : https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/description/
 */

#include <iostream>
#include <vector>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,abm,bmi2")

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

/*
 * kadane's algorithm 是一種用於尋找 subarray 最大值的方式。
 * 原理：
 * 假設現在有 array : [n1, n2, n3, n4, ...]，從頭開始遍歷 array，
 * 令當前 index = i，若 (arr[i] + max(sum(arr[:i-1]))) > 0 則
 * 可以將 arr[i] 加入至目前最大的 subarray 來擴展，若 < 0 則要拋棄
 * 該 subarray，從下一個新的 element 開始建構，因為 sum(arr[:i]) < 0
 * 的 subarray 沒必要再去擴展，從新建構比較好。
 *
 * 該題目要求的是絕對值的最大值，因此我們可以分兩次，一次求最大一次求最小，
 * 比較兩者絕對值較大者就可得到答案。
 */

class Solution {
  public:
    auto maxAbsoluteSum(std::vector<int> &nums) -> int {
        // flag 用於分辨當前要找 subarray 最大值或最小值
        auto kadane_algorithm = [&](int flag) -> int {
            int cur = 0, ret = 0;
            for (const int &num : nums) {
                if ((cur + num) * flag > 0) {
                    cur += num;
                    ret = std::max(ret, cur * flag);
                }
                else {
                    cur = 0;
                }
            }
            return ret;
        };

        return std::max(kadane_algorithm(1), kadane_algorithm(-1));
    }
};