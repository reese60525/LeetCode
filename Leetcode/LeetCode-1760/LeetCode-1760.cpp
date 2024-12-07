#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int minimumSize(std::vector<int> &nums, int maxOperations) {
        int max_num = 0; // 計算 upper bound
        for (int n : nums) {
            max_num = std::max(max_num, n);
        }

        int l = 1, r = max_num;
        while (l < r) {
            int mid = (l + r) / 2;
            int op_count = 0; // 計算當前操作次數

            for (int n : nums) {
                // 跳過不用操作的數，避免無所謂的除法運算
                if (n > mid) {
                    op_count += (n - 1) / mid;
                }
            }

            if (op_count > maxOperations) {
                l = mid + 1;
            }
            else {
                r = mid;
            }
        }

        return r;
    }
};

int main() {

    return 0;
}