#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int maximumLength(std::string s) {
        int n = s.size(), len = 0; // 紀錄當前 special substring 的長度
        // 紀錄每種字母的前三長的 special substring 長度
        std::vector<std::priority_queue<int, std::vector<int>, std::greater<int>>> freq(26);

        // 遍歷 s，將每個字元的 special substring 的每種長度出現的次數記錄到 freq 中
        for (int i = 0; i < n; ++i) {
            ++len;

            // 遍歷到最後一個字元 或是 當前字元和下一個字元不同時，代表一個 special substring 結束
            if (i == n - 1 || s[i] != s[i + 1]) {
                freq[s[i] - 'a'].push(len);

                // 維護 pq 的 size 為 3
                if (freq[s[i] - 'a'].size() > 3) {
                    freq[s[i] - 'a'].pop();
                }

                len = 0;
            }
        }

        int res = 0;
        // 遍歷 freq，找出最長的 special substring 的長度
        for (auto &pq : freq) {
            // 如果 pq 是空的，代表沒有這種字母的 special substring，跳過
            if (pq.empty()) {
                continue;
            }

            // 如果 pq element 數量小於 3，先 push 0 直到有三個
            // 這樣的話就算只有一種長度的 special substring 也能進行後續的長度計算
            // 而不用一堆 if 來判斷修改怎麼計算長度
            while (pq.size() < 3) {
                pq.push(0);
            }

            // pq 是 min heap，依序 push 出最小、中間、最大的長度
            // 由於 len 是從 index = 2 往前填，所以 len[0] 是最小的，len[2] 是最大的
            int len[3] = {0};
            while (!pq.empty()) {
                len[pq.size() - 1] = pq.top();
                pq.pop();
            }

            // 開始進行比較
            res = std::max({res, (len[0] - 2), std::min(len[0] - 1, len[1]), len[2]});
        }

        // res = 0 代表沒有任何 special substring，回傳 -1
        return res == 0 ? -1 : res;
    }
};

int main() {

    return 0;
}