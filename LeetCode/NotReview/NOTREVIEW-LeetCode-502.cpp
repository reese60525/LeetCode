/*
 * 題目: https://leetcode.com/problems/ipo/description/
 *
 * 題目解釋:
 *
 * 思路:
 *
 * 解法:
 *
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int findMaximizedCapital(int k, int w, std::vector<int> &profits, std::vector<int> &capital) {
        int n = profits.size();
        std::vector<std::pair<int, int>> vec;

        for (int i = 0; i < profits.size(); ++i) {
            vec.push_back({capital[i], profits[i]});
        }
        std::sort(vec.begin(), vec.end());

        int vec_index = 0;
        std::priority_queue<int> pq;
        while (k--) {
            while (vec_index < n && w >= vec[vec_index].first) {
                pq.push(vec[vec_index].second);
                ++vec_index;
            }
            if (pq.empty()) {
                break;
            }
            w += pq.top();
            pq.pop();
        }

        return w;
    }
};

int main() {

    return 0;
}