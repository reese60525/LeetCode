/*
 *  Author      : Reese
 *  Created On  : 2024-12-19 11:56
 *  Description : https://leetcode.com/problems/max-chunks-to-make-sorted-ii/description/
 */

#include <iostream>
#include <stack>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int maxChunksToSorted(std::vector<int> &arr) {
        std::stack<int> st;

        for (int n : arr) {
            // n 無法自己成為 subarray，需要將所有 max_val > n 的 subarray 合併
            if (!st.empty() && st.top() > n) {
                // 紀錄新 subarray 的 max value，正好是當前的 top
                int max_val = st.top();
                while (!st.empty() && st.top() > n) {
                    st.pop();
                }
                st.push(max_val);
            }
            // n 能自己成為 subarray，直接 push 到 stack
            else {
                st.push(n);
            }
        }

        return st.size();
    }
};

// class Solution {
//   public:
//     int maxChunksToSorted(std::vector<int> &arr) {
//         size_t n = arr.size();
//         std::vector<int> prefix_max(arr.size()), suffix_min(arr.size());
//         // 紀錄 prefix_max 和 suffix_min
//         for (size_t i = 0; i < n; ++i) {
//             prefix_max[i] = (i == 0) ? arr[i] : std::max(prefix_max[i - 1], arr[i]);
//             suffix_min[n - i - 1] = (i == 0) ? arr[n - 1] : std::min(suffix_min[n - i], arr[n - i - 1]);
//         }

//         int res = 0;
//         // 用 arr[i] 的 prefix_max 和 arr[i+1] suffix_min 來判斷是否能形成 subarray
//         // 因此只需要檢查到 arr[n-2] 即可，因為 arr[n-1] 沒有 suffix_min 可以比較
//         for (size_t i = 0; i < n - 1; ++i) {
//             res += (prefix_max[i] <= suffix_min[i + 1]);
//         }

//         // res 是分割線的數量，一個分割線可以分割出兩個 subarray
//         // 因此 subarray 數量為 res + 1
//         return res + 1;
//     }
// };

int main() {

    return 0;
}