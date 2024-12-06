/*
 * 題目： https://leetcode.com/problems/jump-game-ii/description/
 *
 * 題目解釋：
 * 給一組 integer array，array[i] 表示從 index i 可以跳到的最遠距離，求從 index = 0 到
 * index = array_size -1 的最小跳躍次數。
 * e.g.
 * array = {2, 3, 1, 1, 4}
 * 可以從 index 0 -> index 1 -> index 4，最小跳躍次數為 2。
 * array = {2, 1, 2, 1 ,1, 5}
 * 可以從 index 0 -> index 2 -> index 4 -> index 5，最小跳躍次數為 3。
 *
 * 思路：
 * 方法 1：使用 greedy algorithm
 * 每次從某個節點 i 跳躍時，選擇節點 i 所能跳躍到的各個節點中，能跳最遠的節點。舉例來說，當
 * array[i] = 3，則可以從 index i 跳到 index i+1, i+2, i+3，而這三個節點k所能跳躍的最
 * 遠距離就是 k + array[k]，假設 array[i+1 ~ i+3] = {6, 1, 2}，則各自能跳躍的最大距離
 * 為 {i+1+6, i+2+1, i+3+2} = {i+7, i+3, i+5}，因此從節點 i 出發，選擇節點 i+2 能夠跳
 * 得最遠。從另外一個角度來看，節點 i+2 最遠能跳到節點 i+7，而這跳躍的範圍已經包含了節點 i+1 和
 * i+3 的所有可跳躍範圍，因此這兩個節點可以不用考慮。
 * e.g.
 * array = {2, 1, 2, 1, 1, 4}
 * 一開始只能跳到 index 0，jump_count + 1，接著在 index 0 所能跳躍的範圍內，選擇能跳最遠的，
 * 也就是 index 2，jump_count + 1，接著在 index 2 所能跳躍的範圍內，選擇能跳最遠的，也就是
 * index 4，jump_count + 1，此時 index 4 能直接跳到終點，跳出迴圈，因此最小跳躍次數為 3。
 *
 * 方法 2：使用 BFS
 * 使用 BFS 來解題，將節點 i 所能跳躍的範圍內的節點加入 queue 中，並且將節點 i 標記為已經走過，
 * 同一層的節點都處理完後跳躍次數 + 1，直到某個節點走到終點，則回傳跳躍次數。
 *
 * 方法 3：使用 DP
 * 使用 DP 來解題，dp[i] 表示從 index 0 到 index i 的最小跳躍次數，遍歷 array，對於每個節點
 * i，更新節點 i 所能跳躍的範圍內的節點的跳躍次數。i 表示當前節點，j 表示當前節點所能跳躍的範圍內的節點，
 * 也就是節點 i 能直接跳到節點 j，j 從 i + 1 開始，到 i + nums[i] 結束，如果 dp[j] > dp[i] + 1，
 * 則 dp[j] = dp[i] + 1，反之則不更新。可得到轉移公式：dp[j] = min(dp[j], dp[i] + 1)。
 * e.g.
 * array = {2, 3, 1, 1, 4}，dp[0] = 0，dp[i != 0] = INT_MAX
 * 當 i = 0 時，j = [1, 2]
 * dp[1] = min(dp[1], dp[0] + 1) = 1，dp[2] = min(dp[2], dp[0] + 1) = 1
 * 當 i = 1 時，j = [2, 4]
 * dp[2] = min(dp[2], dp[1] + 1) = 1，dp[3] = min(dp[3], dp[1] + 1) = 2，
 * dp[4] = min(dp[4], dp[1] + 1) = 2
 * 當 i = 2 時，j = [3, 4]
 * dp[3] = min(dp[3], dp[2] + 1) = 2，dp[4] = min(dp[4], dp[2] + 1) = 2
 * 當 i = 3 時，j = [4]
 * dp[4] = min(dp[4], dp[3] + 1) = 2
 * 當 i = 4 時，j = []，跳出迴圈
 * 因此最小跳躍次數為 dp[array_size - 1] = dp[4] = 2。
 */
#include <atomic>
#include <iostream>
#include <unordered_set>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 方法 1：greedy algorithm
class Solution {
  public:
    int jump(std::vector<int> &nums) {
        // 跳躍次數
        int res = 0;
        // 當前能跳躍的最大距離
        int max_jump = 0;
        // 當前節點所能跳躍的範圍，例如節點 i 所能跳躍的範圍為 [i, i+nums[i]]
        // 則 end 為 i+nums[i]
        int end = 0;

        for (int i = 0; i < nums.size(); ++i) {
            // 如果能跳躍的範圍已經超過或等於 array 的範圍，則跳出迴圈
            // 表示已經能直接跳到最後一個節點，因此不需要再跳躍
            if (end >= nums.size() - 1) {
                break;
            }

            // 更新當前能跳躍的最大距離
            max_jump = std::max(max_jump, i + nums[i]);

            // 如果已經達到當前節點能跳躍的範圍，則跳躍次數 + 1，並且更新當前能跳躍的範圍
            // 例如 array[0] = 2，則當前能跳躍的範圍為 [0, 2]，當 i = 2 時必須跳躍一次
            // 這時會選擇能跳最遠的節點，新節點的範圍就是 max_jump，因此更新 end = max_jump
            if (i == end) {
                ++res;
                end = max_jump;
            }
        }

        return res;
    }
};

// // 方法 2：BFS
// class Solution {
//   public:
//     int jump(std::vector<int> &nums) {
//         int res = 0;
//         std::queue<int> q;
//         std::bitset<10000> visited;

//         q.push(0);
//         visited.set(0);

//         while (!q.empty()) {
//             int q_size = q.size();

//             // 處理當前 queue 裡的所有節點，因為 bfs 需要將同一層全部處理完才能進到下一層
//             for (int i = 0; i < q_size; ++i) {
//                 int curr = q.front();
//                 q.pop();

//                 // 如果已經跳到最後一個節點，則回傳跳躍次數
//                 if (curr == nums.size() - 1) {
//                     return res;
//                 }

//                 // 當前節點所能跳躍的範圍不能超過 nums.size() - 1
//                 int end = std::min(curr + nums[curr], static_cast<int>(nums.size()) - 1);
//                 // 將當前節點所能跳躍的範圍內的節點加入 queue 中
//                 for (int j = curr + 1; j <= end; ++j) {
//                     // 如果該節點已經走過，則跳過
//                     if (visited[j]) {
//                         continue;
//                     }

//                     q.push(j);
//                     visited.set(j);
//                 }
//             }
//             // 同一層全部處理完，跳躍次數 + 1
//             ++res;
//         }

//         // 如果無法跳到最後一個節點，則回傳 -1，但題目有保證一定可以跳到最後一個節點
//         return -1;
//     }
// };

// // 方法 3：DP
// class Solution {
//   public:
//     int jump(std::vector<int> &nums) {
//         // dp[i] 表示從 index 0 跳到 index i 的最小跳躍次數
//         std::vector<int> dp(nums.size(), INT_MAX);
//         dp[0] = 0;

//         for (int i = 0; i < nums.size(); ++i) {
//             // 當前節點所能跳躍的範圍不能超過 nums.size() - 1
//             int end = std::min(i + nums[i], static_cast<int>(nums.size()) - 1);
//             // 更新從 i + 1 到 i + nums[i] 之間的節點的跳躍次數
//             for (int j = i + 1; j <= end; ++j) {
//                 dp[j] = std::min(dp[j], dp[i] + 1);
//             }
//         }

//         return dp[nums.size() - 1];
//     }
// };

int main() {

    return 0;
}