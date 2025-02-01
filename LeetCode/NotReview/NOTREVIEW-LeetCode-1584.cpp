/*
 * 題目:
 * https://leetcode.com/problems/min-cost-to-connect-all-points/description/
 *
 * 題目解釋:
 * 給n組座標，請算出走訪所有座標所需要的最小路徑，並且不能重複走訪一個點，路徑長以manhattan
 * distance來計算， 假設有兩點(x1, y1)、(x2, y2)，manhattan distance為|x1 - x2|
 * + |y1 - y2|。
 *
 * 思路:
 * 標準的Minimal Spanning
 * Tree(最小生成樹MST)問題，可以用Prime或是Kruskal演算法來處理，由於測資最多達n
 * = 1000，推薦使用
 * Prime，因為Kruskal是以所有路徑的可能從最小開始走訪，有n的點就需要n * (n-1) /
 * 2筆路徑資料，格式為{點1之座標, 點2之座標, weight} ，約為n^2 /
 * 2，再加上排序的話總體時間複雜度高達O(n^2 * long
 * n)，而Prime由於是根據目前以走訪的點，從這些點的可走路徑來判斷要走哪，
 * 因此路徑數據量是慢慢遞增，資料式通常為(下個目的地點, weight)，最多有2 *
 * n筆資料，而資料是每走過一個點就會新增，所以通常用priority
 * queue來維護，時間複雜度為O(nlogn)，因此會比Kruskal快上不少。
 * 以上所有時間複雜度我都不確定正不正確，看看就好，但Prime是真的快很多。
 *
 * 解法:
 * 1.Prime:
 * 建立pq用來存放目前可選的所有點和weight的資料，weight越小則在pq權重越高，用visited紀錄走訪過的點，visited_count計算已走訪幾個點，
 * 每到一個新點，就把該點所以能走且不重複的資料放入pq，以此循環直到pq為空或是所有點都走過了。
 * 2.Kruskal and UnionFind:
 *
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

static const auto io_sync_off = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return nullptr;
}();

// Prime algorithm and Priority Queue
class Solution {
public:
  struct cmp {
    bool operator()(const auto &a, const auto &b) {
      return a.second > b.second; // 想要讓數值小的在pq的top，
    }
  };

  int minCostConnectPoints(std::vector<std::vector<int>> &points) {
    int n = points.size(), res = 0,
        visited_count = 0; // visited_count用以計算目前走訪了幾個點
    std::vector<bool> visited(n, false); // 紀錄每個點的走訪狀態，走訪過的為true
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        cmp>
        pq; // distance最短的在pq中權重最高

    pq.push(std::pair(
        0,
        0)); // 先放入一開始要走訪的點，並先把distance設為0，因為此時還沒和任何點相連
    // pq不為空，且已經過的點得小於總共的點的數量，若==n代表所有點都走過了，這條件在大測資能大幅優化效率
    while (!pq.empty() && visited_count < n) {
      // 拿出目前的點的points_index和distance
      int cur_node = pq.top().first;
      int cur_weight = pq.top().second;
      pq.pop();
      if (visited[cur_node]) { // 走訪過則不能再次走訪
        continue;
      }
      visited[cur_node] = true;
      ++visited_count;
      res += cur_weight;
      // 把與目前該點所有連接的線路放入pq
      for (int j = 0; j < n; ++j) {
        if (!visited
                [j]) { // 若該線路的點走訪過則不再次走訪，避免graph形成環狀迴圈
          int weight = std::abs(points[cur_node][0] - points[j][0]) +
                       std::abs(points[cur_node][1] - points[j][1]);
          pq.push(std::pair(j, weight));
        }
      }
    }
    return res;
  }
};

// // Kruskal algorithm and UnionFind
// class Solution {
//   public:
//     static bool cmp(const std::vector<int> &a, const std::vector<int> &b) {
//         return a[2] < b[2];
//     }

//     int minCostConnectPoints(std::vector<std::vector<int>> &points) {
//         int n = points.size(), res = 0;
//         std::vector<int> parent(n);
//         std::vector<std::vector<int>> edges(n * (n - 1) / 2,
//         std::vector<int>(3, 0));

//         for (int i = 0; i < n; ++i) {
//             parent[i] = i;
//         }

//         int index = 0;
//         for (int i = 0; i < points.size() - 1; ++i) {
//             for (int j = i + 1; j < points.size(); ++j) {
//                 int distance = std::abs(points[i][0] - points[j][0]) +
//                 std::abs(points[i][1] - points[j][1]); edges[index][0] = i;
//                 edges[index][1] = j;
//                 edges[index][2] = distance;
//                 ++index;
//             }
//         }

//         std::sort(edges.begin(), edges.end(), cmp);

//         for (auto i : edges) {
//             if (findRoot(i[0], parent) != findRoot(i[1], parent)) {
//                 res += i[2];
//                 unionFind(i[0], i[1], parent);
//             }
//         }

//         return res;
//     }

//   private:
//     int findRoot(int x, std::vector<int> &parent) {
//         while (x != parent[x]) {
//             x = parent[x] = parent[parent[x]];
//         }
//         return x;
//     }

//     void unionFind(int x, int y, std::vector<int> &parent) {
//         parent[findRoot(x, parent)] = findRoot(y, parent);
//     }
// };

int main() { return 0; }