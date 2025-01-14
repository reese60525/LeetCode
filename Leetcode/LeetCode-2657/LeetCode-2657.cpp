/*
 *  Author      : Reese
 *  Created On  : 2025-01-14 08:44
 *  Description : https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<int> findThePrefixCommonArray(std::vector<int> &A, std::vector<int> &B) {
        int n = A.size();
        bool is_exist[n + 1];
        std::memset(is_exist, false, sizeof(is_exist));

        int cnt = 0;
        std::vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            (!is_exist[A[i]]) ? is_exist[A[i]] = true : ++cnt;
            (!is_exist[B[i]]) ? is_exist[B[i]] = true : ++cnt;
            res[i] = cnt;
        }

        return res;
    }
};

int main() {

    return 0;
}