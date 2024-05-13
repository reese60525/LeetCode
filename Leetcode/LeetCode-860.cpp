#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    bool lemonadeChange(std::vector<int> &bills) {
        int bill_table[3](0, 0, 0);
        for (auto i : bills) {
            if (i == 5) {
                ++bill_table[0];
            }
            else if (i == 10) {
                ++bill_table[1];
                --bill_table[0];
            }
            else {
                ++bill_table[2];
                if (bill_table[1] > 0) {
                    --bill_table[0];
                    --bill_table[1];
                }
                else {
                    bill_table[0] -= 3;
                }
            }
            if (bill_table[0] < 0 || bill_table[1] < 0)
                return false;
        }
        return true;
    }
};
int main() { return 0; }