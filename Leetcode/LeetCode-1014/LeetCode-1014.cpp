/*
 *  Author      : Reese
 *  Created On  : 2024-12-27 09:13
 *  Description : https://leetcode.com/problems/best-sightseeing-pair/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int maxScoreSightseeingPair(std::vector<int> &values) {
        // max_left[i] 為 k = [0,i-1] 之間的 max(values[k] - k)
        int max_left = values[0] + 0, res = 0;

        for (int i = 1; i < values.size(); ++i) {
            res = std::max(res, (values[i] - i) + max_left);
            max_left = std::max(max_left, values[i] + i);
        }

        return res;
    }
};

int main() {

    return 0;
}