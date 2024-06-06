/*
 * 題目: https://leetcode.com/problems/hand-of-straights/description/
 *
 * 題目解釋:
 *
 * 思路:
 *
 * 解法:
 *
 */
#include <iostream>
#include <map>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    bool isNStraightHand(std::vector<int> &hand, int groupSize) {
        std::map<int, int> table;

        // 如果hand數量不能整除groupSize則必定為false
        if (hand.size() % groupSize) {
            return false;
        }
        // build table
        for (int &i : hand) {
            ++table[i];
        }

        // find answer
        auto t = table.begin();
        for (int i = 0; i < table.size() - groupSize + 1; ++i, ++t) {
            if (t->second == 0) {
                continue;
            }

            auto t1 = t;
            for (int j = 1; j < groupSize; ++j) {
                ++t1;
                if ((t->first + j != t1->first) || (t1->second -= t->second) < 0) {
                    return false;
                }
            }
            t->second = 0;
        }

        return table.rbegin()->second == 0 ? true : false;
    }
};

int main() {

    return 0;
}