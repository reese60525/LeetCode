/*
 * 題目: https://leetcode.com/problems/most-profit-assigning-work/description/
 *
 * 題目解釋:
 *
 * 思路:
 *
 * 解法:
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int maxProfitAssignment(std::vector<int> &difficulty, std::vector<int> &profit, std::vector<int> &worker) {
        int res = 0, cur_profit = 0, n = worker.size();
        std::vector<std::pair<int, int>> table(difficulty.size());

        for (int i = 0; i < difficulty.size(); ++i) {
            table[i] = {difficulty[i], profit[i]};
        }
        std::sort(table.begin(), table.end());
        std::sort(worker.begin(), worker.end());

        for (int i = 0, j = 0; i < n; ++i) {
            while (j < n && worker[i] >= table[j].first) {
                cur_profit = cur_profit > table[j].second ? cur_profit : table[j].second;
                ++j;
            }
            res += cur_profit;
        }

        return res;
    }
};

int main() {

    return 0;
}