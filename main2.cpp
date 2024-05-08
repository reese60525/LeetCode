/*
 * 解法:
 */
#include <algorithm>
#include <functional>
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
    void radix_sort(std::vector<std::pair<int, int>> &nums) {
        std::vector<std::pair<int, int>> bucket[1024]; // 1024*1024 > 1e6(測資範圍)
        // first round
        for (auto &i : nums) {
            // 取二進位的後10bits, EX: 10010101 & 00001111 = 00000101
            bucket[i.first & 1023].emplace_back(i);
        }
        int index = 0;
        for (auto &i : bucket) {
            for (auto &j : i) {
                nums[index++] = j;
            }
            i.clear();
        }
        // second round
        for (auto &i : nums) {
            // 取二進位的前10bits, EX: 10010101 >> 4 = 1001
            bucket[i.first >> 10].emplace_back(i);
        }
        index = 0;
        for (auto &i : bucket) {
            for (auto &j : i) {
                nums[index++] = j;
            }
        }
    }
    std::vector<std::string> findRelativeRanks(std::vector<int> &score) {
        std::vector<std::string> ans(score.size());
        std::vector<std::pair<int, int>> table;

        for (int i = 0; i < score.size(); ++i)
            table.emplace_back(score[i], i);
        radix_sort(table);
        ans[table[0].second] = "Gold Medal";
        if (score.size() > 1)
            ans[table[1].second] = "Silver Medal";
        if (score.size() > 2)
            ans[table[2].second] = "Bronze Medal";
        for (int i = 3; i < score.size(); ++i) {
            ans[table[i].second] = std::to_string(i + 1);
        }
        return ans;
    }
};
int main() { return 0; }