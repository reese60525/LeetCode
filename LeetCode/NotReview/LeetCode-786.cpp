/*
 * 解法1:暴力解
 * 把所有相除的結果由小到大排序，再輸出第k個，時間複雜度O(n^2*log(n^2))。
 *
 * 很棒的講解 : https://www.youtube.com/watch?v=ZzfXmZgJ0cw
 * 配合圖片 :　https://imgur.com/a/bAVLtm2
 * 解法2:binary search
 * 由於小質數除以大質數的商必為0 < quotient < 1，邊界初始值為l = 0, r = 1，
 * mid = (l + r) / 2，用binary search來計算每次小於等於mid的質數組合(n)，
 * 若是n剛好等於k則代表現在小於等於mid的質數組合之最大值即為答案。
 * 時間複雜度O(nlogn)。
 */
#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// binary search，最佳解
class Solution {
  public:
    std::vector<int> kthSmallestPrimeFraction(std::vector<int> &arr, int k) {
        int size = arr.size(); // arr的size
        float l = 0, r = 1;
        while (l <= r) {
            float mid = l + (r - l) / 2;
            // total來計算當前小於mid的質數組合數，ans[2]紀錄當前最大值的質數。
            int total = 0, j = 1, ans[2] = {1, 0x3f3f3f3f};
            // 內迴圈循環找<=mid的質數組合數，i迴圈用來迭代分子
            for (int i = 0; i < size - 1; ++i) {
                // j迴圈用來迭代分母，注意!j不用每次都從i+i開始迭代，可以沿用上次所找到的j繼續往後使用
                // 舉個例子，上次在arr[i]/arr[j]找到比mid小的質數組合，所以此時會跳出j迴圈，而下一次
                // i迴圈迭代時，i = i + 1，此時分子為arr[i + 1]，而要找<=mid的組合，分子變大，分母
                // 不需要變小，直接使用上次的分母往後開始找就好。
                // EX:1, 3, 11, 13, 19, 37, 79, 89。假設上次在i = 1，j = 5找到比mid小的質數組合，
                // 也就是arr[1]和arr[5] => 3/37，那麼在j迴圈中，3/37、3/79、3/89都會比mid小，所以此
                // 時的total為total += size - j，也就是total + 3，而下次i迭代時，i = 2，j = 5，會
                // 從11/37開始，而上次是在3/37找到<=mid，因此沒必要讓j從i +1開始遍歷，直接從上次的j開始
                // 就好，簡單來說分子變大，分母不用再從小到大，直接用上次j迴圈的結果開始往後找更大的分母組合。
                // 因此內迴圈的時間複雜度從普通的O(n^2)變成O(n)。
                while (j < size && arr[i] > arr[j] * mid)
                    ++j;
                if (j == size) // 即arr[i]當分子時，所有分母都不能滿足商<=mid，直接終止i迴圈
                    break;
                total += size - j; // 更新total
                if (total > k) {   // 如果total大於題目要求的數量，縮小binary search的右邊界
                    r = mid;
                    break;
                }
                if (1.0 * ans[0] / ans[1] < 1.0 * arr[i] / arr[j]) { // 更新最大值
                    ans[0] = arr[i];
                    ans[1] = arr[j];
                }
            }
            if (total == k) // 當<=mid的質數組合等於k時，其中的最大值為答案。
                return {ans[0], ans[1]};
            else if (total < k) // 如果total大於題目要求的數量，縮小binary search的左邊界
                l = mid;
        }
        return {};
    }
};

// // 暴力解
// class Solution {
//   public:
//     // 比較函數，a/b < c/d => ad < cb，乘法運算比較快，記得要加static。
//     static bool comp(const std::pair<int, int> &a, const std::pair<int, int> &b) { return a.first * b.second < b.first * a.second; }
//     std::vector<int> kthSmallestPrimeFraction(std::vector<int> &arr, int k) {
//         std::vector<std::pair<int, int>> table; // 格式{(x, y),()...}，x = arr[i]，y = arr[j]，x < y。
//         // build table
//         for (int i = 0; i < arr.size() - 1; ++i)
//             for (int j = i + 1; j < arr.size(); ++j)
//                 table.emplace_back(std::pair(arr[i], arr[j]));
//         // sort as ascending order
//         std::sort(table.begin(), table.end(), comp);
//         // TEST : 印出排序後的table
//         // for (auto i : table) {
//         //     std::cout << "first:" << i.second.first << ", second:" << i.second.second << ", value:" << i.first << '\n';
//         // }
//         return std::vector<int> {table[k - 1].first, table[k - 1].second};
//     }
// };

int main() { return 0; }