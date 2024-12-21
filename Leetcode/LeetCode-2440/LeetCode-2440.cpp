/*
 *  Author      : Reese
 *  Created On  : 2024-12-21 14:23
 *  Description : https://leetcode.com/problems/create-components-with-same-value/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

/*
 *  Author      : Reese
 *  Created On  : 2024-12-21 14:23
 *  Description : https://leetcode.com/problems/create-components-with-same-value/description/
 */

// 將 adj 鄰接圖表創建為全域變數，這樣可以提高效能和降低記憶體使用率
// 如果是在 class 內創建，每次呼叫 maxKDivisibleComponents() 都得重新分配和釋放記憶體
const int N = 2e4 + 5;
std::vector<std::vector<int>> adj(N);

class Solution {
  public:
    int dfs(int pre_node, int curr_node, const std::vector<int> &values, const int &k) {
        // 計算當前節點的子樹總和
        int sum = values[curr_node];
        for (auto &next_node : adj[curr_node]) {
            if (next_node != pre_node) {
                sum += dfs(curr_node, next_node, values, k);
            }
        }

        // 如果當前節點的子樹總和等於 k，該子樹可以被分割，返回上一層繼續檢查其他子樹
        if (sum == k) {
            return 0;
        }
        return sum;
    }

    int componentValue(std::vector<int> &nums, std::vector<std::vector<int>> &edges) {
        // 清空 adj 鄰接圖表，避免之前的測試資料影響當前測試資料的結果
        int sum = 0, n = nums.size();
        for (int i = 0; i < nums.size(); ++i) {
            adj[i].clear();
            sum += nums[i];
        }

        // 創建鄰接圖表
        for (auto &edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // tree 可以被分成 [1, n] 個子數，且題目要求"最多"的子樹，所以從 n 開始遍歷到 1
        // 因為是從最多子樹的方法開始遍歷，一旦找到一個可以均分的方法，該方法必為分割最多子樹的方法，可以直接跳出迴圈
        for (int i = n; i > 0; --i) {
            // 整個樹的總和必須可以被 i 整除，否則無法均分
            if (sum % i != 0) {
                continue;
            }

            // 若 dfs 返回 0，表示可以將子樹分割成 i 個子樹，且每個子樹的值總和相等
            // 題目求可以分割幾次，return i - 1
            if (dfs(-1, 0, nums, sum / i) == 0) {
                return i - 1;
            }
        }

        return -1;
    }
};

int main() {

    return 0;
}