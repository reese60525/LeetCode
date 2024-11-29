/*
 * 題目： https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/description/
 *
 * 題目解釋：
 * 給一個自然數(0 ~ n) matrix，初始位置在(0, 0)，time = 0，每移動一格則time+1，可以重複移動到走過的格子，
 * 每一格都有一個數，如果走到該格時time < grid[x][y]，則該格不可走，求從(0, 0)走到(m-1, n-1)所需要的最小
 * time，如果沒有辦法走到終點則return -1(這種情況只有在起點的周遭都比1大時才會發生)。
 * e.g.
 *        {0, 1, 3, 2}
 * grid = {5, 1, 2, 5}
 *        {4, 3, 8, 6}
 *
 * 剛開始t = 0，所以grid[0][0] = 0能走。t = 1，grid[0][1] = 1能直接走，如果想走到grid[1][0] = 5，
 * 可以在grid[0][0]和grid[0][1]之間來回走，從(0, 1)走回(0, 0)此時t = 2，從(0, 0)走回(0, 1)此時t = 3，
 * 從(0, 1)走回(0, 0)此時t = 4，這時候走到(1, 0)時t = 5，而grid[1][0] = 5，所以就能走到該格。
 * 對於這個grid，最小time的路徑有兩種。
 * 路徑1:(0, 0)->(0, 1)->(1, 1)->(1, 2)->(1, 1)->(1, 2)->(1, 3)->(2, 3)，最小花費的time = 7
 * 路徑2:(0, 0)->(0, 1)->(1, 1)->(1, 2)->(0, 2)->(0, 3)->(1, 3)->(2, 3)，最小花費的time = 7
 *
 * 思路：
 * 使用Dijkstra's Algorithm。
 * 每走到一個新的node後計算從當前node走到下個node所需要的time，將這些的node加入至所有目前可走的node中，
 * 挑選目前能走到的節點中time最小的來走，重複這個動作直到走到終點即可得到答案。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int minimumTime(std::vector<std::vector<int>> &grid) {
        // 如果起點的周遭都比1大，則無法走到終點
        if (grid[0][1] > 1 && grid[1][0] > 1) {
            return -1;
        }

        auto cmp = [](std::tuple<int, int, int> a, std::tuple<int, int, int> b) {
            return std::get<2>(a) > std::get<2>(b); // pq的優先判斷是!cmp，所以min heap要用「大於」
        };

        int m = grid.size(), n = grid[0].size();
        int dir[5] = {0, 1, 0, -1, 0}; // 方向:右、下、左、上
        std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, decltype(cmp)> pq;
        pq.push({0, 0, 0}); // 放入起點

        while (!pq.empty()) {
            auto [x, y, time] = pq.top();
            pq.pop();

            // 往四個方向走
            for (int i = 0; i < 4; ++i) {
                int nx = x + dir[i];
                int ny = y + dir[i + 1];

                // 超出範圍或已走過
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] == -1) {
                    continue;
                }

                // 計算從(x, y)走到(nx, ny)所需要的time
                int next_time = time + 1;
                if (grid[nx][ny] > next_time) {
                    // grid[nx][ny]和next_time的差值是偶數，next_time會是grid[nx][ny]，基數則next_time會是grid[nx][ny]+1
                    next_time = (grid[nx][ny] - next_time) % 2 == 0 ? grid[nx][ny] : grid[nx][ny] + 1;
                }

                // 走到終點
                if (nx == m - 1 && ny == n - 1) {
                    return next_time;
                }

                pq.push({nx, ny, next_time});
                grid[nx][ny] = -1; // visited
            }
        }

        return -1;
    }
};

int main() {

    return 0;
}