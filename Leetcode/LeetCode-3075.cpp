/*
 * 解法:
 * 求最大值，先由大排到小，for跑k round一個一個累加，並且設一個變數來累加每次
 * happy減少的值，當遇到happiness[i] <= n時，代表從此開始的happy值都為0，
 * 即可return sum。
 * P.S. sum會out of int range，記得用long long type。
 */
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    long long maximumHappinessSum(std::vector<int> &happiness, int k) {
        int n = 0; // 計算目前要扣多少happiness
        long long sum = 0;
        std::sort(happiness.begin(), happiness.end(), std::greater<int>()); // 大到小排序
        for (int i = 0; i < k; ++i) {
            if (happiness[i] <= n)
                return sum;
            sum += happiness[i];
            sum -= n;
            ++n;
        }
        return sum;
    }
};
int main() { return 0; }