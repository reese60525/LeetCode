#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    typedef std::pair<int, int> PII;
    int maxTwoEvents(std::vector<std::vector<int>> &events) {
        // 將所有 events 依照 start time 由小到大排序
        std::sort(events.begin(), events.end(), [](const std::vector<int> &a, const std::vector<int> &b) {
            return a[0] < b[0];
        });

        // pre_max 用來紀錄目前 event[i] 之前的最大 event value
        int res = 0, pre_max = 0;
        // 建立 以 endTime 排序 min heap priority queue
        std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;
        // 遍歷 events 找最大值
        for (auto &event : events) {
            // 將 pq 中的 event 與當前 event[i] 不重疊則進去更新 pre_max
            while (!pq.empty() && pq.top().first < event[0]) {
                // 更新 pre_max
                pre_max = std::max(pre_max, pq.top().second);
                pq.pop();
            }

            // 更新 res
            res = std::max(res, event[2] + pre_max);

            // 如果 event[i] 的 value 比 pre_max 大，則將 event[i] 加入 pq
            if (event[2] > pre_max) {
                pq.push({event[1], event[2]});
            }
        }

        return res;
    }
};

int main() {

    return 0;
}