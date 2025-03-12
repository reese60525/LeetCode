/*
 *  Author      : Reese
 *  Created On  : 2025-03-07 16:01
 *  Description :
 */

#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,abm,bmi2")

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    auto closestPrimes(int left, int right) -> std::vector<int> {
        std::vector<int> res(2, -1);
        int pre = -1, dist = INT_MAX;

        // Since 1 is not a prime number and 2 is the only even prime, we start the loop from 3
        if (left < 3) {
            pre = 2, left = 3;
        } else if ((left & 1) == 0) {
            ++left;
        }

        for (int i = left; i <= right; i += 2) {
            // Cannot achieve a smaller dist, so break early.
            if (dist < 3) {
                break;
            }

            // check if i is a prime number
            bool isPrime = true;
            for (int j = 3, len = std::sqrt(i); j <= len; j += 2) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }

            // update res
            if (isPrime) {
                if (pre != -1 && i - pre < dist) {
                    res[0] = pre;
                    res[1] = i;
                    dist = res[1] - res[0];
                }
                pre = i;
            }
        }

        return res;
    }
};