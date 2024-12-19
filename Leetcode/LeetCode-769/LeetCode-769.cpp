/******************************************
 *  File        : main.cpp
 *  Author      : Reese
 *  Created On  : 2024-12-19 08:41
 *  Description : https://leetcode.com/problems/max-chunks-to-make-sorted/description/
 ******************************************/

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int maxChunksToSorted(std::vector<int> &arr) {
        int res = 0, n = arr.size(), max_val = 0;

        for (int i = 0; i < n; ++i) {
            max_val = std::max(max_val, arr[i]);
            res += (i == max_val);
        }

        return res;
    }
};

int main() {

    return 0;
}