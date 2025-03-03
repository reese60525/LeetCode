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
    std::unordered_map<int, int> parent;

    int longestConsecutive(std::vector<int> &nums) {
        std::unordered_map<int, int> groups; // used to record how many different roots

        // initialize parent and unite neighboring number
        for (auto &i : nums) {
            parent[i] = i;
            //  unite neighboring number
            if (parent.count(i - 1)) { // check if i-1 exist
                unionFind(i, i - 1);
            }
            if (parent.count(i + 1)) { // check if i+1 exist
                unionFind(i + 1, i);
            }
        }

        // path compression
        for (auto i : parent) {
            int num = i.first;
            ++groups[findRoot(num)];
        }

        // find longestConsecutive
        int res = 0;
        for (auto &i : groups) {
            res = std::max(res, i.second);
        }

        return res;
    }

  private:
    int findRoot(int &x) {
        return x == parent[x] ? x : parent[x] = findRoot(parent[x]);
    }

    void unionFind(int x, int y) {
        parent[findRoot(x)] = findRoot(y);
    }
};

int main() {
    return 0;
}