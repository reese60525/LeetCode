/*
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
    bool solve(int begin, int &end, int x, int &sum, std::vector<int> &height) {
        int pothole = 0;
        for (int i = begin + x; i != end; i += x) {
            if (height[i] >= height[begin]) {
                sum += (height[begin] * (std::abs(i - begin) - 1));
                sum -= pothole;
                pothole = 0;
                begin = i;
            }
            else if (i == height.size() - 1) {
                end = begin - 1;
                return true;
            }
            else {
                pothole += height[i];
            }
        }
        return false;
    }
    int trap(std::vector<int> &height) {
        int sum = 0, end = height.size();
        if (solve(0, end, 1, sum, height))
            solve(height.size() - 1, end, -1, sum, height);
        return sum;
    }
};
int main() { return 0; }