/*
 * 題目： https://leetcode.com/problems/most-beautiful-item-for-each-query/description/
 *
 * 題目解釋：
 * 給2d integer array，items = {{p1,b1},{p2,b2}...}，和integer array，queries = {q1,q2...}，
 * items中的p代表price，b代表beauty，求所items中price <= queries[i]的maximum beauty並回傳。
 * e.g. items = {{1, 2}, {3, 2}, {2, 4}, {5, 6}, {3, 5}}，queries = {2, 1, 3, 5, 1, 3}
 * 對於queries[i] = 1，price <= 1的item有{1, 2}，因此maximum beauty為2。
 * 對於queries[i] = 2，price <= 2的item有{1, 2}, {2, 4}，因此maximum beauty為4。
 * 對於queries[i] = 3，price <= 3的item有{1, 2}, {3, 2}, {2, 4}, {3, 5}，因此maximum beauty為5。
 * 對於queries[i] = 5，price <= 5的item有{1, 2}, {3, 2}, {2, 4}, {5, 6}, {3, 5}，因此maximum beauty為6。
 * ans = {4, 2, 5, 6, 2, 5}
 *
 * 思路：
 * 方法1:
 * 將items依照price由小到大排序，遍歷並計算每個price的maximum beauty，若有相同的price則合併，
 * 之後遍歷queries，對於queries[i]，在items中使用binary search找到price <= queries[i]的item，
 * 並將maximum beauty更新到queries[i]，最後return queries。
 * 其實並不用對items中相同的price做合併，在price由小到大排序的items中，將maximum beauty往後更新
 * 到items，e.g. items = {{1, 3},{1, 2},{1, 4},{1, 1}}，遍歷items，如果前一個item的beauty
 * 比較大，就將當前的beauty更新為前一個item的beauty，最後items = {{1, 3},{1, 3},{1, 4},{1, 4}}，後續
 * 在做binary search時，只需要兩個判斷，第一個:item[j][0] <= queries[i]時，更新max beauty，l = mid +1，
 * 第二個:item[j][0] > queries[i]，r = mid - 1。這樣一來就算items中有相同的price，也會持續往相同price
 * 的右端靠近(有maximum beauty)。

 * 方法2:
 * 將items依照price由小到大排序，遍歷更新每個price的maximum beauty，如果前一個item的beauty比較大，
 * 就將當前的beauty更新為前一個item的beauty，接著創建array: q_index來存放queries的index，並使用
 * 排序依照queries[q_index[i]]由小到大來排序q_index，q_index為queries中最小值的index排到queries中最
 * 大值的index，接著遍歷q_index，對於queries[q_index[i]]來說就是在由小到大遍歷queries，然後在裡面遍歷
 * items，直到price > queries[q_index[i]]，此時前一個item的beauty為該queries的maximum beauty。
 * 依序將maximum beauty更新到queries即可得到答案。
 */
#include <algorithm>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// // 方法1
// class Solution {
//   public:
//     std::vector<int> maximumBeauty(std::vector<std::vector<int>> &items, std::vector<int> &queries) {
//         // 將items依照price由小到大排序
//         std::sort(items.begin(), items.end(), [](auto &a, auto &b) {
//             return a[0] < b[0];
//         });

//         // 計算每個price的maximum beauty，若有相同的price則合併
//         int max_beauty = -1e9 - 1, items_size = 0; // items_size用來記錄新的items大小
//         for (int i = 0; i < items.size(); ++i) {
//             max_beauty = std::max(max_beauty, items[i][1]);
//             // 若下一個price與當前price相同則跳過
//             if (i < items.size() - 1 && items[i][0] == items[i + 1][0]) {
//                 continue;
//             }
//             else {
//                 // 將當前price與maximum beauty直接從index = 0 覆蓋items，節省空間
//                 items[items_size][0] = items[i][0];
//                 items[items_size][1] = max_beauty;
//                 ++items_size;
//             }
//         }

//         for (int i = 0; i < queries.size(); ++i) {
//             // 對queries進行二分搜尋
//             int l = 0, r = items_size - 1, target = 0;
//             while (l <= r) {
//                 int mid = (l + r) / 2;
//                 if (items[mid][0] == queries[i]) {
//                     target = items[mid][1];
//                     break;
//                 }
//                 else if (items[mid][0] < queries[i]) {
//                     // 用來記錄找不到queries[i]時，最接近queries[i]的maximum beauty
//                     target = items[mid][1];
//                     l = mid + 1;
//                 }
//                 else {
//                     r = mid - 1;
//                 }
//             }
//             queries[i] = target;
//         }

//         return queries;
//     }
// };

// 方法2
class Solution {
  public:
    std::vector<int> maximumBeauty(std::vector<std::vector<int>> &items, std::vector<int> &queries) {
        // 將items依照price由小到大排序
        std::sort(items.begin(), items.end(), [](auto &a, auto &b) {
            return a[0] < b[0];
        });
        // 往後更新每個price的maximum beauty
        for (int i = 1; i < items.size(); ++i) {
            items[i][1] = (items[i][1] < items[i - 1][1]) ? items[i - 1][1] : items[i][1];
        }

        // 建立queries的index，初始化為0,1,2,3...
        std::vector<int> queries_index(queries.size());
        for (int i = 0; i < queries_index.size(); ++i) {
            queries_index[i] = i;
        }
        // 依照queries[queries_index[i]]由小到大排序，queries_index第一個元素為queries中最小值的index
        std::sort(queries_index.begin(), queries_index.end(), [&](int a, int b) {
            return queries[a] < queries[b];
        });

        int i = 0;
        // 遍歷queries_index，queries_index第一個元素為queries中最小值的index
        // 因此是從queries中最小值開始遍歷，直到queries最大值，依序更新queries為maximum beauty
        for (auto &index : queries_index) {
            // 遍歷items，直到price > queries[index]，此時前一個item的beauty為該queries的maximum beauty
            for (; i < items.size(); ++i) {
                if (items[i][0] > queries[index]) {
                    break;
                }
            }
            // 若i = 0，代表items中沒有item的price <= queries[index]，queries[index] = 0
            queries[index] = (i > 0) ? items[i - 1][1] : 0;
        }

        return queries;
    }
};

int main() {

    return 0;
}