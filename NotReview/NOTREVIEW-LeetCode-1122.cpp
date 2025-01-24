/*
 * 題目: https://leetcode.com/problems/relative-sort-array/description/
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
    std::vector<int> relativeSortArray(std::vector<int> &arr1, std::vector<int> &arr2) {
        int arr1_index = 0;
        std::map<int, int> table;

        for (int &i : arr1) {
            ++table[i];
        }

        for (int &i : arr2) {
            for (int j = 0; j < table[i]; ++j) {
                arr1[arr1_index] = i;
                ++arr1_index;
            }
            table[i] = 0;
        }

        for (auto &t : table) {
            for (int i = 0; i < t.second; ++i) {
                arr1[arr1_index] = t.first;
                ++arr1_index;
            }
        }

        return arr1;
    }
};

int main() {

    return 0;
}