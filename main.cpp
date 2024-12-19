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
        std::stack<int> min_stack, max_stack;
        for (int n : arr) {
            while (!max_stack.empty() && max_stack.top() > n) {
                max_stack.pop();
            }
            max_stack.push(n);

            while (!min_stack.empty() && min_stack.top() > n) {
                min_stack.pop();
            }
            min_stack.push(n);
        }

        // while (!st.empty()) {
        //     std::cout << st.top() << '\n';
        //     st.pop();
        // }

        return 0;
    }
};
// 1 3 > 1 3 > 3
// 1 3 1 > 1 1 > 3 1
// 1 3 1 3 > 1 1 3 > 3 3
// 1 3 1 3 4 > 1 1 3 4 > 3 3 4
// 1 3 1 3 4 4 > 1 1 3 4 4 > 3 3 4 4
// 1 3 1 3 4 4 2 > 1 1 2 > 3 3 2

int main() {

    return 0;
}