/*
 *  Author      : Reese
 *  Created On  : 2024-12-29 18:24
 *  Description : https://leetcode.com/problems/rank-teams-by-votes/description/
 */

#include <algorithm>
#include <functional>
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
        // 取負號方便排序，假如投票數全都一樣，則 'A' = 0 = -0，'D' = 3 = -3
        // 0 > -3 會優先排在前面，和比較投票數的邏輯一樣
        std::vector<std::vector<int>> cnt(26, std::vector<int>(27));
        for (int i = 0; i < 26; ++i) {
            cnt[i][26] = -i;
        }
        // 計算每個隊伍在每個投票位置的得票數
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int c = votes[j][i] - 'A';
                ++cnt[c][i];
            }
        }

        // 對 cnt 升序排序
        std::sort(cnt.begin(), cnt.end(), std::greater<>());

        // 將排序後的隊伍編號轉換為字串
        std::string res;
        for (int i = 0; i < m; ++i) {
            // cnt 最後一個 element 是隊伍的編號，要記得將負號轉正
            res += (-cnt[i].back() + 'A');
        }

        return res;
    }
};

int main() {

    return 0;
}