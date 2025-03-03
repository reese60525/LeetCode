/*
 *  Author      : Reese
 *  Created On  : 2025-02-25 13:59
 *  Description : https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/description/
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
 * 解法:
 * 假設有 arr = [n1, n2, n3]，如果現在新增一個數 n4，則新的 arr' = [n1, n2, n3, n4]，
 * 新增了 4 個 subarray : [[n1, n2, n3, n4], [n2, n3, n4,], [n3, n4], [n4]]
 * 要判斷這四個新的 subarray 總和的奇偶姓，可以用 `偶 + 偶 = 偶`、`奇 + 偶 = 奇` 來統計
 *
 * 從頭遍歷 arr，同時計算所有以最後一個 element 為結尾的 subarray 其總和是奇偶數的數量，
 * 當新增一個奇數時，奇數 subarray 數量 = 原本偶數數量 + 1，偶數數量 = 原本奇數數量，
 * 當新增一個偶數時，奇數數量不變，偶數數量 + 1，每次都將奇數 subarray 加到 res，結束遍歷
 * 即可得到答案。
 */

class Solution {
  public:
    auto numOfSubarrays(std::vector<int> &arr) -> int {
        int n = arr.size();
        int odd_cnt = 0, even_cnt = 0;
        long long res = 0;

        for (int num : arr) {
            if (num & 1) {
                int tmp = odd_cnt;
                odd_cnt = even_cnt + 1;
                even_cnt = tmp;
            }
            else {
                ++even_cnt;
            }
            res += odd_cnt;
        }

        return res % int(1e9 + 7);
    }
};