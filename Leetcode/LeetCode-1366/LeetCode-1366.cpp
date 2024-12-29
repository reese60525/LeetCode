/*
 *  Author      : Reese
 *  Created On  : 2024-12-29 18:24
 *  Description : https://leetcode.com/problems/rank-teams-by-votes/description/
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::string rankTeams(std::vector<std::string> &votes) {
        int n = votes.size(), m = votes[0].size();

        // cnt[][26] 紀錄這筆資料是哪個隊伍的
        std::vector<std::vector<int>> cnt(26, std::vector<int>(27));
        for (int i = 0; i < 26; ++i) {
            cnt[i][26] = i;
        }
        // 計算每個隊伍在每個投票位置的得票數
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int c = votes[j][i] - 'A';
                ++cnt[c][i];
            }
        }

        // 對 cnt 排序
        std::sort(cnt.begin(), cnt.end(), [&](auto &a, auto &b) {
            for (int i = 0; i < 26; ++i) {
                // 比較每個投票位置的得票數
                if (a[i] == b[i]) {
                    continue;
                }
                return a[i] > b[i];
            }
            // 如果得票數都相同，則比較隊伍的編號
            return a[26] < b[26];
        });

        // 將排序後的隊伍編號轉換為字串
        std::string res;
        for (int i = 0; i < m; ++i) {
            // cnt 最後一個 element 是隊伍的編號
            res += (cnt[i].back() + 'A');
        }

        return res;
    }
};

int main() {

    return 0;
}