#include <iostream>
#include <string>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int longestIdealString(std::string s, int k) {
        int dp[26], largest_len = 0;
        memset(dp, 0, sizeof(dp));

        for (auto i : s) {
            int new_dp = 0;
            for (int j = 0; j < 26; ++j) {
                if (abs(i - 'a' - j) <= k)
                    new_dp = std::max(new_dp, dp[j]);
            }
            dp[i - 'a'] = new_dp + 1;
        }

        for (auto i : dp)
            largest_len = std::max(largest_len, i);

        return largest_len;
    }
};

int main() {
    Solution solution;
    int k;
    std::string s;
    while (std::cin >> s >> k)
        std::cout << solution.longestIdealString(s, k) << '\n';
    return 0;
}