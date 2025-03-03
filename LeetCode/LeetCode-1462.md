# <center> [1462. Course Schedule IV](https://leetcode.com/problems/course-schedule-iv/description/) </center>

## 題目敘述

[![](https://i.imgur.com/jTTTHbh.png)](https://i.imgur.com/jTTTHbh.png)

給定整數 `numCourses` 表示課程數量，以及二維整數陣列 `prerequisites` 和 `queries`， $prerequisites[i] = [a, b]$ 表示 `a` 是 `b` 的前置課程，要學 `b` 課程之前必須先學 `a`， $queries[i] = [a, b]$ 表示要 **查詢** `a` 是否為 `b` 的前置課程，請將所有查詢結果存入 bool array 中並回傳。

## 解題思路

### 1. Topological Sorting

假設有個課程關係為： $prerequisites = [[A, B], [B, C]]$ ，也就是：

- `A` 是 `B` 的前置課程。

- `B` 是 `C` 的前置課程。

- 那麼 `A` 也會是 `C` 的前置課程。

因此不僅僅是要處理 `prerequisites` 中每一對 `[A, B]` 的關係，也要將所有 `A` 的前置課程加入至 `B` 的前置課程中。

可以使用 topological sorting 來對每個節點進行處理，這樣可以保證每個節點的 **前置課程都處理完後** 才會處理該節點。

舉例來說，現在有個課程關係為： $prerequisites = [[A, B], [B, C], [C, D], [D, E]]$ ，也就是 `A -> B -> C -> D -> E`

- 若第一個處理的節點是 `C`，由於 `C` 的前置課程都尚未被處理，因此當前 `C` 沒有任何前置課程（`A`、`B`）被記錄，這會導致 `D` 只會記錄到 `C` 是他的前置課程，`A` 和 `B` 都沒有被記錄到 `D` 的前置課程中。

- 若我們按照 topological sorting 來處理：

  - 首先處理 `A`，`A` 沒有前置課程需要紀錄

  - 接著處理 `B`，紀錄 `A` 為 `B` 的前置課程。

  - 接著處理 `C`，紀錄 `B` 為 `C` 的前置課程，並且將 `B` 的所有前置課程（`A`）也記錄為 `C` 的前置課程。

  - 接著處理 `D`，紀錄 `C` 為 `D` 的前置課程，並且將 `C` 的所有前置課程（`A`、`B`）也記錄為 `D` 的前置課程。

  - 以此類推 ......，最終就能將所有前置課程的資訊記錄起來，用於回答 `queries`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  private:
    // chain forward star
    int index;                     // 邊的編號
    int ne[4950];                  // 下條邊的編號（index）
    int to[4950];                  // 當前邊所指向的節點
    int he[100];                   // 每個節點的第一條邊
    int inDegree[100];             // 每個節點的 in degree
    bool isPrerequisite[100][100]; // 用來判斷節點 u 是否為 v 的前置課程

    // 新增邊
    void add(int u, int v) {
        to[index] = v;
        ne[index] = he[u];
        he[u] = index++;
    }

  public:
    Solution() {
        index = 0;
        std::memset(he, -1, sizeof(he));
        std::memset(inDegree, 0, sizeof(inDegree));
        std::memset(isPrerequisite, 0, sizeof(isPrerequisite));
    }

    std::vector<bool> checkIfPrerequisite(int numCourses, std::vector<std::vector<int>> &prerequisites,
                                          std::vector<std::vector<int>> &queries) {
        // 添加邊到 chain forward star，並計算 in degree
        for (auto &e : prerequisites) {
            isPrerequisite[e[0]][e[1]] = true;
            add(e[0], e[1]);
            ++inDegree[e[1]];
        }

        // 將 in degree = 0 的節點加入至 queue 中
        std::queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (!inDegree[i]) {
                q.push(i);
            }
        }

        // topological sorting
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // 遍歷節點 u 的所有邊，將其邊指向的節點 v 的 in degree - 1
            for (int i = he[u]; i != -1; i = ne[i]) {
                int v = to[i];
                // 節點 u 是 v 的前置課程，則所有 u 的前置課程也會是 v 的前置課程
                // 遍歷所有 u 的前置課程，將其標記為 v 的前置課程
                for (int j = 0; j < numCourses; ++j) {
                    isPrerequisite[j][v] |= isPrerequisite[j][u];
                }
                // 將 in degree = 0 的節點加入至 queue 中
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // 處理所有查詢
        std::vector<bool> res(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            res[i] = isPrerequisite[queries[i][0]][queries[i][1]];
        }

        return res;
    }
};
```

[![](https://i.imgur.com/VowuXkA.png)](https://i.imgur.com/VowuXkA.png)

#### 複雜度分析

令 $N = numCourses$ 為課程總數量， $E = prerequisites.size()$ 為前置課程的數量， $Q = queries.size()$ 為查詢的數量。

- 時間複雜度： $O(N^3 + Q)$

  - 添加邊和計算 in degree 要遍歷所有前置課程，共 $O(E)$ 。

  - 初始化 queue，將所有 $\text{in degree} = 0$ 的節點加入至 queue 要遍歷所有課程，共 $O(N)$ 。

  - 在 topological sorting 過程中

    - 外部迴圈（`while (!q.empty())`） 每個課程最多進入和彈出 queue 一次，共 $O(N)$ 。

    - 內部迴圈（遍歷 `u` 的所有鄰接節點 `v`），所有邊都會被遍歷一次，共 $O(E)$ 。

    - 在內部迴圈中更新 `isPrerequisite` 要遍歷所有課程，需要 $O(N)$ ，因此每條邊都會需要 $O(N)$ 次操作來更新 `isPrerequisite`， 共 $O(N \cdot E)$ 。

    - 合計需要 $O(N \cdot E)$ 。

  - 處理查詢需要遍歷 `queries`，共 $O(Q)$ 。

  - 以上合計為： $O(E) + O(N) + O(N \cdot E) + O(Q) = O(N \cdot E + Q)$ ，最糟情況下 $E = N^2$ ，則會變成 $O(N^3 + Q)$ 。

- 空間複雜度： $O(N^2)$

  - 紀錄所有前置課程關係 `isPrerequisite` 需要 $O(N^2)$ 。

  - 記錄所有邊 `prerequisites` 需要 $O(E)$ 。

  - 以上合計為： $O(N^2) + O(E) = O(N^2 + E)$ ，最糟情況下 $E = N^2$ ，則會變成 $O(N^2)$ 。

---

將以上做法進一步優化，由於只需要判斷節點 `u` 和節點 `v` 的 **可達性**，將 `isPrerequisite` 改為 `std::bitset<100> isPrerequisite[100]`，`isPrerequisite[u]` 用來紀錄 `u` 的所有前置課程，如果 $isPrerequisite[u][v] = true$ 表示 `v` 是 `u` 的前置課程。

在原本的做法中需要遍歷所有節點來確認該節點是否為 `u` 的前置課程，是的話則將其也設定為 `v` 的前置課程，整個過程需要 $O(N)$ 的時間。根據前置課程的 **遞移性** ，可以將這個過程改為執行 `isPrerequisite[v] |= isPrerequisite[u]` 就能讓 `v` 繼承 `u` 的所有前置課程，整個過程只要 $O(\frac{N}{w})$ ，其中 `w` 為 `cpu 的 word size`，通常 $w = 64$ ，在這個題目中節點數 $N \leq 100$ ，因此時間複雜度 $\approx O(N^2 + Q)$ ，當 $N \gg 64$ 時，時間複雜度仍為 $O(\frac{N^3}{w} + Q) = O(N^3 + Q)$ 。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  private:
    // chain forward star
    int index;                            // 邊的編號
    int ne[4950];                         // 下條邊的編號（index）
    int to[4950];                         // 當前邊所指向的節點
    int he[100];                          // 每個節點的第一條邊
    int inDegree[100];                    // 每個節點的 in degree
    std::bitset<100> isPrerequisite[100]; // 用來判斷節點 u 是否為 v 的前置課程

    // 新增邊
    void add(int u, int v) {
        to[index] = v;
        ne[index] = he[u];
        he[u] = index++;
    }

  public:
    Solution() {
        index = 0;
        std::memset(he, -1, sizeof(he));
        std::memset(inDegree, 0, sizeof(inDegree));
    }

    std::vector<bool> checkIfPrerequisite(int numCourses, std::vector<std::vector<int>> &prerequisites,
                                          std::vector<std::vector<int>> &queries) {
        // 添加邊到 chain forward star，並計算 in degree
        for (auto &e : prerequisites) {
            isPrerequisite[e[1]][e[0]] = true;
            add(e[0], e[1]);
            ++inDegree[e[1]];
        }

        // 將 in degree = 0 的節點加入至 queue 中
        std::queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (!inDegree[i]) {
                q.push(i);
            }
        }

        // topological sorting
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // 遍歷節點 u 的所有邊，將其邊指向的節點 v 的 in degree - 1
            for (int i = he[u]; i != -1; i = ne[i]) {
                int v = to[i];
                // 節點 u 是 v 的前置課程，則所有 u 的前置課程也會是 v 的前置課程
                // 遍歷所有 u 的前置課程，將其標記為 v 的前置課程
                isPrerequisite[v] |= isPrerequisite[u];
                // 將 in degree = 0 的節點加入至 queue 中
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // 處理所有查詢
        std::vector<bool> res(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            res[i] = isPrerequisite[queries[i][1]][queries[i][0]];
        }

        return res;
    }
};
```

[![](https://i.imgur.com/TvPvr7m.png)](https://i.imgur.com/TvPvr7m.png)

#### 複雜度分析

令 $N = numCourses$ 為課程總數量， $E = prerequisites.size()$ 為前置課程的數量， $Q = queries.size()$ 為查詢的數量。

- 時間複雜度： $O(N^3 + Q)$

- 空間複雜度： $O(N^2)$

### 2. Floyd-Warshall Algorithm

這是一種適合用來處理所有 node pairs 的最短路徑演算法，核心概念是動態規劃，令 `dp[k][i][j]` 表示為可以經過 `[0, 1, ..., k]` 這些中間節點的 `i` 到 `j` 的最短路徑，也就是 $dp[k][i][j] = \min(dp[k-1][i][j], dp[k-1][i][k] + dp[k-1][k][j])$ ，可以發現當前狀態只會與上個狀態有關，因此能將 `dp[k][i][j]` 會壓縮為 `dp[i][j]`，轉移方程式： $dp[i][j] = \min(dp[i][j], dp[i][k] + dp[k][j])$ 。

為何是 `dp[k][i][j]` 而不是 `dp[i][j][k]` 呢？因為要確保每個 `dp` 都已經是最佳解才會算出正確的答案，考慮到以下兩種情況：

- `dp[k][i][j]`：`k` 是最外層的迴圈，因此 `dp[i][k]` 和 `dp[k][j]` 都會受到最外層 `k` 的限制，需要將前 `k` 個中間節點的所有 `dp[i][j]` 最佳解都先算出來才能算將第 `k+1` 個節點當中間點的最佳解，因此 `dp[i][k]` 和 `dp[k][j]` 都是 **當前最佳解**。

- `dp[i][j][k]`：`k` 是最內層的迴圈，`dp[i][k]` 和 `dp[k][j]` 的 `k` 並未受到限制，`k` 可以是 `[0, 1, ..., n]`，例如 $i = 0$ 、 $j = 0$ 、 $k = 73$ ，對於 `dp[0][73]` 而言此時的 `[dp[0][0], dp[0][1], ..., dp[0][73]]` 都尚未算出其最佳解，因此最終答案也會是錯誤的。

如果還是看不懂，可以參考[其他人的解釋](https://www.zhihu.com/question/30955032?sort=created)。

在這道題目可以用 Floyd-Warshall Algorithm 模擬 **遞移閉包（Transitive Closure）** 的特性來解題，將 `dp[k][i][j]` 看作節點 `i` 是否能通過或不通過 `[0, 1, ..., k]` 這些節點當中間點來到達節點 `j`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  private:
  public:
    std::vector<bool> checkIfPrerequisite(int numCourses, std::vector<std::vector<int>> &prerequisites,
                                          std::vector<std::vector<int>> &queries) {
        bool isPrerequisite[numCourses][numCourses]; // 用來判斷節點 u 是否為 v 的前置課程
        std::memset(isPrerequisite, false, sizeof(isPrerequisite));

        // 處理所有輸入的前置課程
        for (auto &pre : prerequisites) {
            isPrerequisite[pre[0]][pre[1]] = true;
        }

        // Floyd-Warshall Algorithm
        for (int k = 0; k < numCourses; ++k) {
            for (int i = 0; i < numCourses; ++i) {
                for (int j = 0; j < numCourses; ++j) {
                    isPrerequisite[i][j] |= isPrerequisite[i][k] & isPrerequisite[k][j];
                }
            }
        }

        // 處理所有查詢
        std::vector<bool> res(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            res[i] = isPrerequisite[queries[i][0]][queries[i][1]];
        }

        return res;
    }
};
```

[![](https://i.imgur.com/c8DgmUK.png)](https://i.imgur.com/c8DgmUK.png)

#### 複雜度分析

令 $N = numCourses$ 為課程總數量， $E = prerequisites.size()$ 為前置課程的數量， $Q = queries.size()$ 為查詢的數量。

- 時間複雜度： $O(N^3 + Q)$

- 空間複雜度： $O(N^2)$
