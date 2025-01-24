/*
 * 題目： https://leetcode.com/problems/check-if-n-and-its-double-exist/description/
 *
 * 題目解釋：
 * 給一個 integer array，檢查是否存在一對數 (x, y) 使得 x = 2y or y = 2x，若存在 return true。
 *
 * 思路：
 * 用 hash map 紀錄每個數是否出現過，遍歷 array 判斷當前的整數 n 是否有符合的 n*2 or n/2 存在。
 * 整數 0 要特別注意，因為 0*2 == 0/2 == 0，因此 map[n] = true 要放到 if() 判斷之後。避免錯誤
 * 判斷 0 的數量。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    bool checkIfExist(std::vector<int> &arr) {
        std::unordered_map<int, bool> map; // 紀錄各個數字是否出現過
        for (int &n : arr) {
            if (map.count(n * 2) || (n % 2 == 0 && map.count(n / 2))) {
                return true;
            }
            // 如果放到前面先做標記，0 被標記為 true，導致只出現 1 次的 0 被誤判為有兩個
            map[n] = true;
        }

        return false;
    }
};

int main() {

    return 0;
}