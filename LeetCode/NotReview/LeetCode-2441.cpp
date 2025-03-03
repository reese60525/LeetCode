/*
 * 解法:
 * num範圍是-1000到1000，不含0，建立一個table[2001]，table[1~1000]用來確認
 * 1~1000是否存在，table[1001~2000]則是確認-1 ~ -1000是否存在，遍歷nums，並
 * 且邊找邊build table。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int findMaxK(std::vector<int> &nums) {
        int max_value = -1;
        bool table[2001];
        memset(table, 0, sizeof(table));
        for (auto i : nums) {
            if (i > 0) {
                if (table[1000 + i])
                    max_value = std::max(max_value, i);
                else
                    table[i] = true;
            }
            else if (table[0 - i])
                max_value = std::max(max_value, 0 - i);
            else
                table[1000 - i] = true;
        }
        return max_value;
    }
};

int main() { return 0; }