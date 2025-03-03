/*
 * 題目: https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/description/
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
    int minMovesToSeat(std::vector<int> &seats, std::vector<int> &students) {
        int res = 0;

        std::sort(seats.begin(), seats.end());
        std::sort(students.begin(), students.end());

        for (int i = 0; i < seats.size(); ++i) {
            res += std::abs(seats[i] - students[i]);
        }

        return res;
    }
};

int main() {

    return 0;
}