/*
 *  Author      : Reese
 *  Created On  : 2024-12-18 08:43
 *  Description : https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/description/
 */

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
    std::vector<int> finalPrices(std::vector<int> &prices) {
        std::stack<int> st;

        // 找右區間第一個小於等於自身的值，從右往左遍歷
        for (int i = prices.size() - 1; i >= 0; --i) {
            while (!st.empty() && st.top() > prices[i]) {
                st.pop();
            }

            int tmp = prices[i]; // 由於 prices[i] 可能會被修改，所以需要暫存
            if (!st.empty()) {
                prices[i] -= st.top();
            }
            st.emplace(tmp);
        }

        return prices;
    }
};

int main() {

    return 0;
}