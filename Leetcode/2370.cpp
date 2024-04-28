#include <iostream>
#include <string>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 思路:遍歷s中每個char(這邊簡稱i)，去比較所有能把i放在後頭的字母(也就是以i為結尾)，找出長度最大的dp[j]，dp[i]=dp[j]+1,
//     最後在從dp中找出最大的值，即為答案。
class Solution {
  public:
    int longestIdealString(std::string s, int k) {
        int dp[26], largest_len = 0;
        memset(dp, 0, sizeof(dp)); // dp初始化，memset(array, 初始值:只能是0, array size(資料型態大小*資料數量))

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