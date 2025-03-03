/*
 * 題目： https://leetcode.com/problems/trapping-rain-water/description/
 *
 * 題目解釋：
 * 給一個整數 array，array[i] 代表在 i 這位置有高度 array[i] 的柱子，求如果下雨了能接
 * 到多少雨水。
 * e.g.
 * array = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}，圖如下所示：
 *
 *                               |
 *                       |       | |   |
 *                 ._|_._|_|_._|_|_|_|_|__|
 *          index: 0 1 2 3 4 5 6 7 8 9 10 11
 * 在 indexs = {{1, 3}, {3, 7}, {8, 10}} 中 分別有 {1, 4, 1} 能街道共 7 體積的雨水
 *
 * 思路：
 * 一根柱子想要接住雨水，前提條件是其左右邊都有比他高的柱子。
 *
 * 方法 1：two pointer
 * 用 l and r 分邊從 array 的兩邊往中間遍歷，並紀錄目前左邊和右邊最高的柱子，因為每次迭代都
 * 會先更新左右邊最高的柱子高度，所以 height[l] <= l_highest、height[r] <= r_highest，
 * 假設時候 height[l] < height[r]，則 height[l] < r_highest，因此要計算 height[l] 的
 * 雨水體積只要將 l_hightest - height[l] 就可得到，所以在選擇左邊還是右邊的柱子時，只要判斷
 * height[l] 和 height[r] 哪個比較小，就選擇那邊的柱子來計算雨水體積。
 *
 * 方法 2：monotonic stack
 * 用一個遞減的 stack 來紀錄目前遍歷過的柱子，當遇到比 stack top 還高的柱子時，因為 stack
 * 是遞減的，所以 stack top 左邊的柱子都會比 stack top 高，此時 stack top 的柱子可以接雨水，
 * 計算出當前柱子和 stack top 的左邊柱子之間的距離，乘上 (左右邊較矮的柱子 - stack top 的高度)，
 * 即為該柱子可以接的雨水體積。如果 stack 為空，則代表 stack top 左邊沒有柱子比它高，無法接住雨水。
 * e.g.
 * height = {1, 3, 2, 1, 2, 2 ,4}
 * index = 0，stack 為空，push 1 到 stack 中，stack = {1}。
 * index = 1，3 比 stack top 高，pop stack，先前的 stack top 左邊沒有柱子能接雨水，
 * push 3 到 stack 中，stack = {3}。
 * index = 2，2 比 stack top 矮，push 2 到 stack 中，stack = {3, 2}。
 * index = 3，1 比 stack top 矮，push 1 到 stack 中，stack = {3, 2, 1}。
 * index = 4，2 比 stack top 高，pop stack，先前的 stack top 左邊柱子為 2，雨水體積為
 * (4 - 2 - 1) * (2 - 1) = 1，繼續比較 2 和 stack top 的關係，stack = {3, 2}，
 * 2 和 stack top 一樣高，push 2 到 stack 中，stack = {3, 2, 2}。
 * index = 5，2 和 stack top 一樣高，push 2 到 stack 中，stack = {3, 2, 2, 2}
 * index = 6，4 比 stack top 高，pop stack，先前的 stack top 左邊柱子為 2，雨水體積為
 * (6 - 4 - 1) * (2 - 2) = 0，繼續比較 4 和 stack top 的關係，stack = {3, 2, 2}，
 * 4 比 stack top 高，pop stack，先前的 stack top 左邊柱子為 2，雨水體積為
 * (6 - 2 - 1) * (2 - 2) = 0，繼續比較 4 和 stack top 的關係，stack = {3, 2}，
 * 4 比 stack top 高，pop stack，先前的 stack top 左邊柱子為 3，雨水體積為
 * (6 - 1 - 1) * (3 - 2) = 4，繼續比較 4 和 stack top 的關係，stack = {3}，
 * 4 比 stack top 高，pop stack，stack 為空，push 4 到 stack，stack = {4}。
 * 遍歷完 array 了，雨水體積共為 1 + 0 + 0 + 4 = 5。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
// 方法 1
class Solution {
  public:
    int trap(std::vector<int> &height) {
        int res = 0, l_highest = 0, r_highest = 0; // 紀錄當前左右邊最高的柱子
        size_t l = 0, r = height.size() - 1;

        while (l < r) {
            // 更新左右邊最高的柱子
            l_highest = std::max(height[l], l_highest);
            r_highest = std::max(height[r], r_highest);

            // 選擇較矮的柱子計算雨水體積
            if (height[l] < height[r]) {
                res += (l_highest > height[l]) ? (l_highest - height[l]) : 0;
                ++l;
            }
            else {
                res += (r_highest > height[r]) ? (r_highest - height[r]) : 0;
                --r;
            }
        }

        return res;
    }
};

// // 方法 2
// class Solution {
//   public:
//     int trap(std::vector<int> &height) {
//         int res = 0;
//         std::stack<int> st;

//         for (size_t r = 0; r < height.size(); ++r) {
//             // 如果當前柱子比 stack top 的柱子高，則 stack top 的柱子可以接住雨水
//             while (!st.empty() && height[r] > height[st.top()]) {
//                 int cur = st.top(); // stack top 的柱子 index
//                 st.pop();

//                 // 如果 stack 已經空了，表示 stack top 左邊沒有柱子了，則無法接住雨水
//                 if (st.empty()) {
//                     break;
//                 }

//                 // 計算 stack top 的柱子能接住多少雨水
//                 int l = st.top(); // stack top 左邊的柱子 index
//                 // 將 stack top 左右邊較小的柱子減去 stack top 的柱子高度，即為 stack top 這一層能接住的雨水高度
//                 int h = std::min(height[l], height[r]) - height[cur];
//                 int w = r - l - 1; // stack top 左右柱子間的寬度
//                 res += h * w;      // 計算雨水體積
//             }

//             st.push(r); // 將當前柱子 index 放入 stack
//         }

//         return res;
//     }
// };

int main() {

    return 0;
}