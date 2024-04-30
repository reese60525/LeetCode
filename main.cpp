#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int coinChange(std::vector<int> &coins, int amount) {
        // test
        std::cout << "amout:" << amount << '\n';
        // test

        int ans = 0, temp_amount = amount;
        std::vector<int> coins_table(coins.size());
        // 大到小排序
        sort(coins.begin(), coins.end(), std::greater {});

        // build coins_table
        temp_amount = amount;
        for (int i = 0; i < coins.size(); ++i) {
            coins_table[i] = temp_amount / coins[i];
            temp_amount %= coins[i];
        }
        // 刪除開頭為0的coin_table直到遇見不為0的
        for (auto i : coins_table) {
            if (i != 0)
                break;
            coins.erase(coins.begin());
            coins_table.erase(coins_table.begin());
        }
        // 若amount == 0輸出答案
        if (temp_amount == 0) {
            for (auto i : coins_table)
                ans += i;
            return ans;
        }
        // 若coin_table只剩下1個則輸出-1
        if (coins.size() == 1)
            return -1;
        // 把大錢分給小錢
        for (int i = coins_table.size() - 2; i >= 0; --i) {}

        // test
        std::cout << "*************************" << '\n';
        for (auto i : coins)
            std::cout << i << ' ';
        std::cout << '\n';
        for (auto i : coins_table)
            std::cout << i << ' ';
        std::cout << "\n*************************" << "\n\n";
        // test
    };

    int main() {
        Solution solution;
        std::vector<int> coins {2, 5, 10};
        int amount = 51;
        std::cout << solution.coinChange(coins, amount);
        return 0;
    }