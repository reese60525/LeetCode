/*
 * 題目： https://leetcode.com/problems/valid-arrangement-of-pairs/description/
 *
 * 題目解釋：
 * 給一組 integer 2d array，array[i] = {xi, yi}，用來表示directed graph，題目保證每個graph
 * 都存在至少一個 path，這個 path 能夠經過每個邊且每個邊"只走過一次"，找出其中一種路徑並回傳。
 * e.g.
 * array = {{5, 1}, {4, 5}, {11, 9}, {9, 4}}
 * path = {{11, 9}, {9, 4}, {4, 5}, {5, 1}}
 * 該 path 是 Eulerian Path。
 * array = {{1, 3}, {3, 2}, {2, 1 }}
 * path = {{1, 3}, {3, 2}, {2, 1}}  or {{2, 1}, {1, 3}, {3, 2}}  or {{3, 2}, {2, 1}, {1, 3}}
 * 該 path 是 Eulerian Path，並且也是 Eulerian Circuit。
 *
 * 思路：
 * 這是一個 Eulerian Path 的問題，可以用 Hierholzer’s algorithm 來解。
 * 關於 Eulerian Path 的介紹：https://www.youtube.com/watch?v=xR4sGgwtR2I&t=0s
 * 關於 Hierholzer’s algorithm 的介紹：https://www.youtube.com/watch?v=8MpoO2zA2l4&t=0s
 * 對於 directed graph，graph 有 Eulerian Path 的條件為：
 * 1.vertice 的 in-degree = out-degree，這種條件會形成 Eulerian Circuit (Eulerian Path 的一種變體)。
 * 2.有一個 vertice 1 的 in-degree = out-degree + 1，且有另一個 vertice 2 的 in-degree = out-degree - 1。
 *   其他所有 vertices 的 in-degree = out-degree。
 * Eulerian Circuit 是 Eulerian Path 的一種變體，形成條件為 Eulerian Path 的起點和終點都是同個 vertice。
 * 只要滿足任一個條件，directed graph 就會存在 Eulerian Path (Eulerian Circuit)。
 *
 * 題目有說一定會有一個 Eulerian Path，所以只要判斷該 path 是條件 1 還是條件 2，接著再用 Hierholzer’s algorithm。
 * Hierholzer’s algorithm 是一個用來找 Eulerian Path 的 algorithm，如果該 directed graph 滿足 條件 1，
 * directed graph 存在 Eulerian Circuit，因此可以用任意一個 vertice 當作起點。如果該 directed graph
 * 滿足 條件 2，directed graph 存在 Eulerian Path，需要找出 in-degree = out-degree + 1 的 vertice 當作起點。
 * Hierholzer’s algorithm 的步驟如下：
 * 1.從起點開始 DFS，把走過的 vertice push 到 stack 中，然後走到下一個 vertice，並把走過的 edge 刪除。
 * 2.當走到一個 vertice 時，如果這個 vertice 沒有其他 edge 可以走，就把該點 push 到 path 中，並且從 stack 中的 pop。
 * 3.重複步驟 1 和 2，直到 stack 為空，此時 path 中就會是 Eulerian Path 的 "倒序"。
 * 4.最後把 path 反轉，就會是 Eulerian Path。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<std::vector<int>> validArrangement(std::vector<std::vector<int>> &pairs) {
        std::unordered_map<int, int> freqs;              // 紀錄每個 vertice 的 in-degree 和 out-degree
        std::unordered_map<int, std::vector<int>> graph; // 建構 directed graph
        for (auto &pair : pairs) {
            ++freqs[pair[0]];                  // 該 vertice 有新的 out-degree 就 + 1
            --freqs[pair[1]];                  // 該 vertice 有新的 in-degree 就 - 1
            graph[pair[0]].push_back(pair[1]); // 每個 vertice 所連通 edge
        }

        // 判斷該 graph 是 Eulerian Path 還是 Eulerian Circuit
        // 如果該 graph 不是 Eulerian Circuit，需要找出 in-degree = out-degree + 1 的 vertice 當作起點
        int head = pairs[0][0]; // 預設起點為 vertice 0
        for (auto &pair : freqs) {
            if (pair.second == 1) {
                head = pair.first;
                break;
            }
        }

        // Hierholzer’s algorithm
        std::stack<int> st;
        st.push(head);
        std::vector<int> path;
        while (!st.empty()) {
            int curr_node = st.top();

            if (graph[curr_node].empty()) {
                st.pop();
                path.push_back(curr_node);
                continue;
            }

            int next_node = graph[curr_node].back();
            graph[curr_node].pop_back();
            st.push(next_node);
        }

        // 把 path 反轉，就會是 Eulerian Path
        std::vector<std::vector<int>> res;
        for (int i = path.size() - 1; i > 0; --i) {
            res.push_back({path[i], path[i - 1]});
        }

        return res;
    }
};

int main() {

    return 0;
}