/*
 * 題目：
 *
 * 題目解釋：
 *
 * 思路：
 *
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    long long pickGifts(std::vector<int> &gifts, int k) {
        std::make_heap(gifts.begin(), gifts.end()); // 原地建立 max heap

        while (k-- && gifts[0] > 1) {
            std::pop_heap(gifts.begin(), gifts.end());  // 將 top 移到 尾端
            gifts.back() = sqrt(gifts.back());          // 將原本的 top 開根號
            std::push_heap(gifts.begin(), gifts.end()); // 將開根號後的 top 重新放入 heap
        }

        // 回傳剩餘 gifts 總額
        return accumulate(gifts.begin(), gifts.end(), 0LL);
    }
};

int main() {

    return 0;
}