/*
 * 題目： https://leetcode.com/problems/maximum-matrix-sum/description/
 *
 * 題目解釋：
 * 給一個整數n*n matrix，可以對matrix的相鄰element做同乘以-1的運算操作，求整個matrix的
 * 總和的最大值。
 * 相鄰的定義:element的上下左右四個方向。
 * e.g.
 *          [ 1   2   3]                        [ 1   2   3]
 * matrix = [-1, -2, -3] ，可以將-2和-3進行操作變成 [-1,  2,  3] ，得max_sum = 16。
 *          [ 1   2   3]                        [ 1   2   3]
 *
 * 思路：
 * 經過觀察，如果matrix中負數是偶數個，則可以透過運算操作將所有的負數變成正數，因此答案為matrix
 * element的絕對值總和。如果負數是奇數個，則可以透過運算操作使得負數變成一個，而我們可以選擇將絕
 * 對值最小的element變成負數，這樣得到的sum是最大的，因此答案為matrix element的絕對值總和減去
 * 絕對值最小的element的兩倍(正數變成負數之間的差值是兩倍)。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    long long maxMatrixSum(std::vector<std::vector<int>> &matrix) {
        int negative_count = 0, k = 0x3f3f3f; // k存儲絕對值最小的element
        long long sum = 0;

        for (auto &row : matrix) {
            for (int n : row) {
                if (n < 0) {
                    ++negative_count;
                }
                k = std::min(k, std::abs(n));
                sum += std::abs(n);
            }
        }

        return (negative_count % 2 == 0) ? sum : sum - 2 * k;
    }
};

int main() {

    return 0;
}