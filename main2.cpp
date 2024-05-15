/*
 * 題目: https://leetcode.com/problems/longest-consecutive-sequence/description/
 * 題目解釋:
 * 思路:
 * 解法:
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::unordered_map<int, int> nums_table;

    int longestConsecutive(std::vector<int> &nums) {
        std::unordered_map<int, int> groups;

        // initialize nums_table and unite neighboring number
        for (auto &i : nums) {
            if (!nums_table.count(i)) { // skip the duplicate numbers.
                nums_table[i] = i;
                if (nums_table.count(i - 1)) {
                    unionFind(i, i - 1);
                }
                if (nums_table.count(i + 1)) {
                    unionFind(i + 1, i);
                }
            }
            else {
                i = 0x3f3f3f3f; // set the duplicate numbers to infinity
            }
        }
        // path compression
        for (auto i : nums) {
            if (i != 0x3f3f3f3f)
                ++groups[findRoot(i)];
        }
        // calculate res
        int res = 0;
        for (auto &i : groups) {
            res = std::max(res, i.second);
        }
        return res;
    }

  private:
    int findRoot(int &x) {
        return x == nums_table[x] ? x : nums_table[x] = findRoot(nums_table[x]);
    }
    void unionFind(int x, int y) {
        nums_table[findRoot(x)] = findRoot(y);
    }
};

int main() {
    return 0;
}