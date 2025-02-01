/*
 * 題目：https://leetcode.com/problems/container-with-most-water/description/
 *
 * 題目解釋：
 * 給一個array，每個element都是一根柱子的高度，找出某兩根柱子，使其之中的水量(面積)為最多。
 *
 * 思路：
 * 使用two pointer algorithm，由於兩柱子之間的水量(面積)是由柱子較短的一方所決定，因此移動
 * 較短的柱子以此來尋找更長的柱子。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int maxArea(std::vector<int> &height) {
        int l = 0, r = height.size() - 1, max = 0;

        while (l < r) {
            max = std::max(max, std::min(height[l], height[r]) * (r - l));
            height[l] < height[r] ? ++l : --r;
        }

        return max;
    }
};

int main() {

    return 0;
}