/*
 * 題目:
 *
 * 題目解釋:
 *
 * 思路:
 *
 * 解法:
 *
 */
#include <algorithm>
#include <iostream>
#include <unordered_map>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    bool isNStraightHand(std::vector<int> &hand, int groupSize) {
        if (hand.size() % 4) {
            return false;
        }

        std::unordered_map<int, int> table;

        // std::sort(hand.begin(), hand.end());
        for (int &i : hand) {
            ++table[i];
        }

        // for (int i = 0; i < hand.size() - 1; ++i) {
        //     if (hand[i] == hand[i + 1]) {
        //         hand[i] = -1;
        //     }
        // }
        // std::sort(hand.begin(), hand.end());
        // int index = -1;
        // while (++index < hand.size()) {
        //     if (hand[index] != -1) {
        //         break;
        //     }
        // }
        // hand.erase(hand.begin(), hand.begin() + index);

        std::sort(table.begin(), table.end());
        for (auto i = table.begin(); i != table.end(); ++i) {}

        // for (int i = 0; i < hand.size(); ++i) {
        //     if (table[i] == 0) {
        //         continue;
        //     }

        //     for (int j = 1; j < groupSize; ++j) {
        //         table[i + j] -= table[i];
        //         if (table[i + j] < 0) {
        //             return false;
        //         }
        //     }
        //     table[i] = 0;
        // }

        return true;
    }
};

int main() {

    return 0;
}