/*
 * 題目： https://leetcode.com/problems/shortest-distance-after-road-addition-queries-i/description/
 *
 * 題目解釋：
 * 給一個數字n表示有n個城市，以及2d integer array queries = {{x1, y1}, {x2, y2}, ...{xn, yn}}，
 * 每個query代表將x到y之間加入一條x通往y的路徑，城市連通的初始狀態為C1 -> C2 -> ... -> Cn。
 * 求每加入一個新的query後，從起點到終點(C0到Cn)的最短路徑。
 *
 * 思路：
 * 用bfs來解決最短路徑問題。先創建一個array shortest_distance用來儲存從C0到Ci的最短距離，
 * 每當有新的query(Cx, Cy)加入時，只會影響到從Cy開始連通的所有城市的最短距離，因此bfs只要
 * 從Cy開始，並且最短距離有變小的城市將其最短距離更新，然後繼續bfs，最後Cn的最短距離即為加入
 * 該query後的最短距離。
 */
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    void findShortestDistance(std::vector<std::vector<int>> &paths, std::vector<int> &shortest_distance,
                              int curr_city) {
        // 遍歷Cy連通的所有city
        for (int next_city : paths[curr_city]) {
            // 只有當連通的city其最短距離能變更小才需要更新其值並繼續bfs
            if (shortest_distance[next_city] > shortest_distance[curr_city] + 1) {
                shortest_distance[next_city] = shortest_distance[curr_city] + 1;
                findShortestDistance(paths, shortest_distance, next_city);
            }
        }
    }

    std::vector<int> shortestDistanceAfterQueries(int n, std::vector<std::vector<int>> &queries) {
        // paths[i]儲存city_i可以直通哪些city
        std::vector<std::vector<int>> paths(n);
        for (int i = 0; i < n - 1; ++i) {
            paths[i].push_back(i + 1);
        }

        // 從起點到每個city的最短距離
        std::vector<int> shortest_distance(n);
        for (int i = 0; i < n; ++i) {
            shortest_distance[i] = i;
        }

        std::vector<int> res(queries.size());
        // 將新的直通路徑加入paths
        for (int i = 0; i < queries.size(); ++i) {
            paths[queries[i][0]].push_back(queries[i][1]);
            // 更新query(Cx, Cy)的Cy最短距離
            shortest_distance[queries[i][1]] =
                std::min(shortest_distance[queries[i][1]], shortest_distance[queries[i][0]] + 1);
            // bfs更新Cy連通的所有城市最短距離
            findShortestDistance(paths, shortest_distance, queries[i][1]);
            res[i] = shortest_distance[n - 1];
        }

        return res;
    }
};

int main() {

    return 0;
}