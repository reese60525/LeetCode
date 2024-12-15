/*
 * 題目：
 *
 * 題目解釋：
 *
 * 思路：
 *
 */
#include <iostream>
#include <queue>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    double maxAverageRatio(std::vector<std::vector<int>> &classes, int extraStudents) {
        // 計算通過率增加量的函數
        auto diff = [](int pass, int total) {
            return static_cast<double>((pass + 1)) / (total + 1) - static_cast<double>(pass) / total;
        };

        double res = 0;
        std::priority_queue<std::pair<double, std::array<int, 2>>> pq;
        for (size_t i = 0; i < classes.size(); ++i) {
            // 將基礎通過率累加到 res 中，這一步驟可以省略後面要遍歷 pq 算出 res 的步驟
            res += static_cast<double>(classes[i][0]) / classes[i][1];
            // 將各班級的通過率增加量和 class 放入 pq 中
            pq.push({
                diff(classes[i][0], classes[i][1]), {classes[i][0], classes[i][1]}
            });
        }

        // 將學生一一分配給通過率增加量最大的班級
        while (extraStudents--) {
            auto [ratio, cls] = pq.top();
            pq.pop();
            // 累加通過率增加量
            res += ratio;
            // 更新 pq
            pq.push({
                diff(cls[0] + 1, cls[1] + 1), {cls[0] + 1, cls[1] + 1}
            });
        }

        return res / classes.size();
    }
};

int main() {

    return 0;
}