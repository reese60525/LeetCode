/******************************************
 *  File        : main.cpp
 *  Author      : Reese
 *  Created On  : 2024-12-19 11:56
 *  Description : https://leetcode.com/problems/max-chunks-to-make-sorted-ii/description/
 ******************************************/

#include <iostream>
#include <stack>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int maxChunksToSorted(std::vector<int> &arr) {
        std::stack<int> st;

        for (int n : arr) {
            if (!st.empty() && st.top() > n) {
                int max_val = st.top();
                while (!st.empty() && st.top() > n) {
                    st.pop();
                }
                st.push(max_val);
            }
            else {
                st.push(n);
            }
        }

        return st.size();
    }
};

// 1 2 3 1 1 2 3 4 3
// 1 > 1
// 1 2 > 1 2
// 1 2 3 > 1 2 3
// 1 2 3 1 > 1 3
// 1 2 3 1 1 > 1 3
// 1 2 3 1 1 2 > 1 3
// 1 2 3 1 1 2 3 > 1 3 3
// 1 2 3 1 1 2 3 4 > 1 3 3 4
// 1 2 3 1 1 2 3 4 3 > 1 3 3 4
// 1 2 3 1 1 2 3 4 1 > 1 4

int main() {
    Solution s;
    std::vector<int> arr = {};
    s.maxChunksToSorted(arr);
    return 0;
}