/*
 *  Author      : Reese
 *  Created On  : 2024-12-29 14:16
 *  Description : https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/description/
 */

#include <climits>
#include <iostream>
#include <numeric>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// Sliding Window
class Solution {
  public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int> &nums, int k) {
        int n = nums.size();

        std::vector<int> res(3);
        int w1_sum = 0, w1_max = 0, w1_max_idx = 0;
        int w2_sum = 0, w12_max = 0, w12_max_idx1 = 0, w12_max_idx2 = 0;
        int w3_sum = 0, w123_max = 0;
        for (int i = 0; i < n - 2 * k; ++i) {
            w1_sum += nums[i];
            w2_sum += nums[i + k];
            w3_sum += nums[i + 2 * k];

            // 所有 window 的長度都是 `k` 後才開始計算
            if (i >= k - 1) {
                if (w1_sum > w1_max) {
                    w1_max = w1_sum;
                    w1_max_idx = i - (k - 1);
                }
                if (w1_max + w2_sum > w12_max) {
                    w12_max = w1_max + w2_sum;
                    w12_max_idx1 = w1_max_idx;
                    w12_max_idx2 = i + 1;
                }
                if (w12_max + w3_sum > w123_max) {
                    w123_max = w12_max + w3_sum;
                    res = {w12_max_idx1, w12_max_idx2, i + k + 1};
                }

                w1_sum -= nums[i - (k - 1)];
                w2_sum -= nums[i + 1];
                w3_sum -= nums[i + k + 1];
            }
        }

        return res;
    }
};

// // Prefix and Suffix
// class Solution {
//   public:
//     std::vector<int> maxSumOfThreeSubarrays(std::vector<int> &nums, int k) {
//         int n = nums.size();

//         // sum[i]表示在 nums 範圍是 [0, i] 中的總合
//         std::vector<int> sum(n, 0);
//         sum[0] = nums[0];
//         for (int i = 1; i < n; ++i) {
//             sum[i] = sum[i - 1] + nums[i];
//         }

//         // left_max[i] 表示在 nums 範圍是 [0, i] 中總和最大的 subarray 的起始 index
//         int max_val = sum[k - 1];
//         std::vector<int> left_max(n, 0);
//         for (int i = k; i < n; ++i) {
//             int cur_val = sum[i] - sum[i - k];
//             if (cur_val > max_val) {
//                 max_val = cur_val;
//                 left_max[i] = i - k + 1;
//             }
//             else {
//                 left_max[i] = left_max[i - 1];
//             }
//         }
//         // right_max[i] 表示在 nums 範圍是 [i, n - 1] 中總和最大的 subarray 的起始 index
//         max_val = sum[n - 1] - sum[n - k - 1];
//         std::vector<int> right_max(n, n - k);
//         for (int i = n - k - 1; i > 0; --i) {
//             int cur_val = sum[i + k - 1] - sum[i - 1];
//             // 當 max_val = cur_val，要選擇起始 index 較小的，所以是 >= 而不是 >
//             if (cur_val >= max_val) {
//                 max_val = cur_val;
//                 right_max[i] = i;
//             }
//             else {
//                 right_max[i] = right_max[i + 1];
//             }
//         }

//         int max_sum = 0;
//         std::vector<int> res(3);
//         // 遍歷中間的 subarray，找出最大的總和和各自的起始 index
//         for (int i = k; i <= (n - 1) - (2 * k - 1); ++i) {
//             int left_idx = left_max[i - 1];
//             int left_val = left_idx == 0 ? sum[left_idx + k - 1] : sum[left_idx + k - 1] - sum[left_idx - 1];
//             int right_idx = right_max[i + k];
//             int right_val = sum[right_idx + k - 1] - sum[right_idx - 1];
//             int cur_val = sum[i + k - 1] - sum[i - 1];

//             if (left_val + cur_val + right_val > max_sum) {
//                 max_sum = left_val + cur_val + right_val;
//                 res[0] = left_idx;
//                 res[1] = i;
//                 res[2] = right_idx;
//             }
//         }

//         return res;
//     }
// };

// // DP
// class Solution {
//   public:
//     std::std::vector<int> maxSumOfThreeSubarrays(std::vector<int> &nums, int k) {
//         int n = nums.size();

//         // 計算 preffix sum，sum[i] 表示前 `i` 個 `nums` 的總和
//         std::vector<int> sum(n + 1, 0);
//         for (int i = 1; i <= n; ++i) {
//             sum[i] = sum[i - 1] + nums[i - 1];
//         }

//         // dp[i][j] 表示前 `i` 個數字中，選擇 `j` 個長度為 `k` 的子數組的最大總和
//         int dp[n + 1][4];
//         std::memset(dp, 0, sizeof(dp));
//         for (int i = k; i <= n; ++i) {
//             for (int j = 1; j <= 3; ++j) {
//                 // 目前能選的數字數量至少要為 `j` 個長度 `k` 的子數組總長度才是有意義的
//                 if (i < j * k) {
//                     dp[i][j] = INT_MIN;
//                     continue;
//                 }
//                 dp[i][j] = std::max(dp[i - 1][j], dp[i - k][j - 1] + sum[i] - sum[i - k]);
//             }
//         }

//         // 回朔找出選擇的 subarray 的最小字典序的起始 index
//         // 若 dp[i][cnt] 不等於 dp[i - 1][cnt]，表示以第 `i` 個數字為結尾的 subarray 被選擇了
//         // subarray 的起始位置是第 `i - k + 1` 個數字，在 `nums` 中的 index 是 `i - k`
//         int i = n, j = 3;
//         std::vector<int> res(3);
//         while (j > 0) {
//             if (dp[i][j] == dp[i - 1][j]) {
//                 --i;
//                 continue;
//             }
//             res[--j] = i - k;
//             i -= k;
//         }

//         return res;
//     }
// };

int main() {

    return 0;
}