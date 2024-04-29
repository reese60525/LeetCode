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
        int ans = 0, temp_amount = amount;
        std::vector<int> coins_table(coins.size());
        // 大到小排序
        sort(coins.begin(), coins.end(), std::greater {});

        while (true) {
            if (coins_table.size() == 1) {
                if (amount >= coins[0] && amount % coins[0] == 0)
                    return amount / coins_table[0];
                else
                    return -1;
            }
            // build coins_table
            temp_amount = amount;
            for (int i = 0; i < coins.size(); ++i) {
                coins_table[i] = temp_amount / coins[i];
                temp_amount %= coins[i];
            }
            // test
            std::cout << "*************************" << '\n';
            for (auto i : coins)
                std::cout << i << ' ';
            std::cout << '\n';
            for (auto i : coins_table)
                std::cout << i << ' ';
            std::cout << "\n*************************" << "\n\n";
            // test
            for (int i = 0; i < coins_table[0]; ++i) {
                int ans = coins_table[0] - i;
                std::cout << "amount:" << amount << '\n';
                temp_amount = (amount % coins[0]) + (coins[0] * i);
                std::cout << "temp:" << temp_amount << '\n';
                for (int i = 1; i < coins.size(); ++i) {
                    coins_table[i] = temp_amount / coins[i];
                    ans += coins_table[i];
                    temp_amount %= coins[i];
                }
                if (temp_amount == 0) {
                    return ans;
                }
            }
            coins.erase(coins.begin());
            coins_table.erase(coins_table.begin());
        }
        return ans;
    }
};

int main() {
    Solution solution;
    std::vector<int> coins {2, 5, 10};
    int amount = 51;
    std::cout << solution.coinChange(coins, amount);
    return 0;
}