/*
 *  Author      : Reese
 *  Created On  : 2024-12-22 09:56
 *  Description : https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/description/
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<int> leftmostBuildingQueries(std::vector<int> &heights, std::vector<std::vector<int>> &queries) {
        std::vector<int> res(queries.size(), -1);
        // v 存放需要額外進行查找的 query 資訊
        std::vector<std::vector<std::pair<int, int>>> v(heights.size());
        for (size_t i = 0; i < queries.size(); ++i) {
            int a = queries[i][0], b = queries[i][1];
            if (a > b) {
                std::swap(a, b);
            }
            // 第一和第二種情況，a 能直接到達 b 的位置
            if (a == b || heights[a] < heights[b]) {
                res[i] = b;
            }
            else {
                // 第三種情況，a 不能直接到達 b 的位置，需要額外進行查找
                v[b].push_back({heights[a], i});
            }
        }

        // min heap
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
        for (size_t i = 0; i < heights.size(); ++i) {
            // 如果當前建築物 i 比 pq top 的 a 還要高，則 i 就是答案
            while (!pq.empty() && pq.top().first < heights[i]) {
                res[pq.top().second] = i;
                pq.pop();
            }

            // 不能一次將所有要查詢的資料全部加入 pq，如果有 query 的 b 比 i 還要右邊時會出錯
            // 每個 query 只能和 b 右邊的建築來比較
            for (std::pair<int, int> &query : v[i]) {
                pq.push(query);
            }
        }

        return res;
    }
};

// class Solution {
//   public:
//     std::vector<int> leftmostBuildingQueries(std::vector<int> &heights, std::vector<std::vector<int>> &queries) {
//         std::vector<int> res(queries.size(), -1);
//         // v 存放需要額外進行查找的 query 資訊
//         std::vector<std::vector<std::pair<int, int>>> v(heights.size());
//         for (size_t i = 0; i < queries.size(); ++i) {
//             int a = queries[i][0], b = queries[i][1];
//             if (a > b) {
//                 std::swap(a, b);
//             }
//             // 第一和第二種情況，a 能直接到達 b 的位置
//             if (a == b || heights[a] < heights[b]) {
//                 res[i] = b;
//             }
//             else {
//                 // 第三種情況，a 不能直接到達 b 的位置，需要額外進行查找
//                 v[b].push_back({heights[a], i});
//             }
//         }

//         std::vector<int> st;
//         // 為了簡單地維護 monotonic stack，需要從右到左遍歷 heights
//         for (size_t i = heights.size() - 1; i < heights.size(); --i) {
//             // 對每個 query 進行 binary search
//             for (auto &[ha, idx] : v[i]) {
//                 int l = 0, r = st.size() - 1;
//                 while (l <= r) {
//                     int mid = l + (r - l) / 2;
//                     if (heights[st[mid]] > ha) {
//                         l = mid + 1;
//                     }
//                     else {
//                         r = mid - 1;
//                     }
//                 }
//                 // 如果有找到比 ha 大的，l = mid + 1，如果 l 是 0 代表找不到比 ha 大的
//                 res[idx] = (l == 0) ? -1 : st[l - 1];

//                 // C++20 的 binary search，主要用於找到第一個大於等於 ha 的元素，並返回其迭代器
//                 // auto it = std::ranges::lower_bound(st, -ha, {}, [&](int j) {
//                 //     return -heights[j];
//                 // });
//                 // res[idx] = it > st.begin() ? *prev(it) : -1;
//             }

//             // 維護 monotonic stack
//             while (!st.empty() && heights[i] >= heights[st.back()]) {
//                 st.pop_back();
//             }
//             st.push_back(i);
//         }

//         return res;
//     }
// };

// class Solution {
//   public:
//     std::vector<int> leftmostBuildingQueries(std::vector<int> &heights, std::vector<std::vector<int>> &queries) {
//         // highest 儲存每個建築物其右邊第一個比自身高的建築物 index
//         std::stack<size_t> st;
//         std::vector<int> highest(heights.size());
//         for (size_t i = heights.size() - 1; i < heights.size(); --i) {
//             while (!st.empty() && heights[i] > heights[st.top()]) {
//                 st.pop();
//             }

//             highest[i] = (st.empty()) ? -1 : st.top();
//             st.push(i);
//         }

//         // 對 queries 進行處理，讓 queries[i][0] <= queries[i][1]
//         for (auto &query : queries) {
//             if (query[0] > query[1]) {
//                 std::swap(query[0], query[1]);
//             }
//         }

//         // 創建 queries_idx 儲存 queries 的 index，對 queries_idx 以 queries[queries_idx[i]][1] 由小到大進行排序
//         // 這樣做的目的是在於達到排序 queries 的同時又能取得該 queries 原本的 index
//         // 例如原本 queries_idx[3] = 3，排序後 queries_idx[3] = 12，能得知 queries_idx[3] 原本在 queries 的 index 為
//         12 std::vector<size_t> queries_idx(queries.size()); std::iota(queries_idx.begin(), queries_idx.end(), 0); //
//         初始化 queries_idx 為 0, 1, 2, 3, ... std::sort(queries_idx.begin(), queries_idx.end(), [&](size_t a, size_t
//         b) {
//             return queries[a][1] < queries[b][1];
//         });

//         // 用 map[i] 儲存曾經查詢過的 query(i, j) 的最新結果
//         std::unordered_map<int, int> mp;
//         std::vector<int> res(queries.size(), -1);
//         for (size_t i = 0; i < queries.size(); ++i) {
//             size_t idx = queries_idx[i]; // 該 query 在 queries 的 index
//             int a = queries[idx][0];     // Alice 所在的建築物 index
//             int b = queries[idx][1];     // Bob 所在的建築物 index

//             // 第一和第二種情況，a 能直接到達 b 的位置
//             if (a == b || heights[a] < heights[b]) {
//                 res[idx] = b;
//                 continue;
//             }

//             // 第三種情況，a 不能直接到達 b 的位置
//             int j = highest[b];
//             // 判斷 mp[a] 是否存在
//             if (mp.find(a) != mp.end()) {
//                 // 如果 mp[a] 或 j 其中一個為 -1 表示無解
//                 // 反之判斷 mp[a] 和 j 誰比較大，mp[a] >= j 則直接用 mp[a] 為解，反之用 j 來往右找解
//                 j = (mp[a] == -1 || j == -1) ? -1 : std::max(j, mp[a]);
//             }

//             while (j > 0 && heights[j] <= heights[a]) {
//                 j = highest[j];
//             }

//             res[idx] = j;
//             mp[a] = res[idx];
//         }

//         return res;
//     }
// };

int main() {

    return 0;
}