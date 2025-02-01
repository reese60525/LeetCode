```cpp
/*
 *  Author      : Reese
 *  Created On  : 2025-01-29 14:22
 *  Description : https://leetcode.com/problems/course-schedule-iv/description/
 */

#include <iostream>
#include <queue>
#include <vector>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,abm,bmi2")

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

struct {
    int ne;
    int to;
} Edges[4955];
int he[105];
int inDegree[105];
std::bitset<10005> isConnected;

class Solution {
  private:
    int index;

    void add(int u, int v) {
        Edges[index].to = v;
        Edges[index].ne = he[u];
        he[u] = index++;
    }

  public:
    std::vector<bool> checkIfPrerequisite(int numCourses, std::vector<std::vector<int>> &prerequisites,
                                          std::vector<std::vector<int>> &queries) {
        index = 0;
        isConnected.reset();
        std::memset(he, -1, sizeof(he));
        std::memset(inDegree, 0, sizeof(inDegree));

        for (auto &e : prerequisites) {
            isConnected[e[0] * numCourses + e[1]] = true;
            add(e[0], e[1]);
            ++inDegree[e[1]];
        }

        std::queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (!inDegree[i]) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i = he[u]; i != -1; i = Edges[i].ne) {
                int v = Edges[i].to;
                for (int j = 0; j < numCourses; ++j) {
                    isConnected[j * numCourses + v] =
                        isConnected[j * numCourses + v] || isConnected[j * numCourses + u];
                }
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        std::vector<bool> res(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            res[i] = isConnected[queries[i][0] * numCourses + queries[i][1]];
        }

        return res;
    }
};

int main() {

    return 0;
}
```
