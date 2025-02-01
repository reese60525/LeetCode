# <center> [802. Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/description/) </center>

## 題目敘述

[![](https://i.imgur.com/VvM0Gk2.png)](https://i.imgur.com/VvM0Gk2.png)

給一個二維整數陣列 `graph` 表示一個有向圖，`graph[i]` 存放節點 `i` 所指向的所有節點。

定義 terminal node 和 safe node 為：

- terminal node：沒有任何指向其他節點的邊，也就是 out degree 為 0。

- safe node：所有的邊都指向 terminal 或是 safe node。

請找出所有的 safe node 並將這些 safe node **升序排序**後回傳。

## 解題思路

### 1. Depth First Search（DFS）

當一個節點是 safe node 時，其所有邊都必需指向 terminal node 或是 safe node，而那些指向 safe node 的邊，不斷深入遍歷之後最終也會指向 terminal node，因此可以將 terminal node 也視為是一種 safe node。

可以用 DFS 來遍歷整個 `graph`，而一個 node 是不是 safe node 可以用以下兩個條件來判斷：

1. 如果該節點的所有邊最後都會來到 terminal node 則表示該節點是 safe node。

2. 如果該節點某條邊在 DFS 過程中經過了已經遍歷過且不是 terminal node 或 safe node 的節點，則會形成環狀迴圈，因此不可能是 safe node。

根據以上條件，這道題目所求的就是所有不會形成環狀迴圈的節點。

演算法流程：

1. 初始化 `std::bitset` 陣列 `state`：

    - `state[i]` 用於表示節點 `i` 是不是 safe node 或 terminal node，若為 0 代表不是這兩種節點之一，若為 1 則是這兩種之一。

    - `state[i + 10000]` 用於表示節點 `i` 是否曾經走過，如果 0 表示沒有走過，若為 1 則已經走過，那麼當前 DFS 路線會形成環，必定不是 safe node。

2. 將每個節點都進行 DFS，在 DFS 過程中如果當前節點已經走過了，直接 return `state[i]` 來判斷，若還沒走過就繼續 DFS。

3. 在將節點一個個 DFS 的過程中把是 safe node 的節點放入 `res` 中，最後 return `res`。

#### 程式碼

```cpp {.line-numbers}
// state[i] 紀錄當前節點是否為 safe node or terminal node
// state[i + 10000] 紀錄是否走過該節點
std::bitset<20005> state;
class Solution {
  public:
    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>> &graph) {
        state.reset();

        auto dfs = [&](auto &&dfs, int node) -> bool {
            // 走過的就直接 return state[i]
            if (state[node + 10000]) {
                return state[node];
            }
            state[node + 10000] = true;

            // 若沒走過就繼續 DFS
            for (int &next : graph[node]) {
                if (!dfs(dfs, next)) {
                    return false;
                }
            }

            // 當所有邊都是指向 safe node 則當前節點也是 safe node
            return state[node] = true;
        };

        // 把所有節點都進行 DFS 檢查是不是 safe node
        std::vector<int> res;
        for (int i = 0; i < graph.size(); ++i) {
            if (dfs(dfs, i)) {
                res.push_back(i);
            }
        }

        return res;
    }
};
```

[![](https://i.imgur.com/WbYIovz.png)](https://i.imgur.com/WbYIovz.png)

#### 複雜度分析

令 $V$ 為圖中節點數量， $E$ 為邊的數量。

- 時間複雜度： $O(V + E)$

    所有節點都只會被檢查一次，所有邊都只會經過一次。

- 空間複雜度： $O(V)$

    `state` 使用了 $O(2V) \approx O(V)$ 的空間。

### 2. Topological Sorting（Kahn's Algorithm）

Topological sorting 是一種常用於**有向無環圖**的排序方式。它將圖中所有節點排成一個線性序列，使得圖中任意一條有向邊 (u, v) 的兩個節點 `u` 和 `v`， `u` 總是排在 `v` 的前面。

用 Kahn's algorithm 來實作 topological sorting，演算法流程如下：

1. 計算每個節點的 in degree，並將 $\text{in degree} = 0$ 的節點加入一個 queue 中。

2. 執行 BFS，從 queue 中取出節點，這些節點都是 $\text{in degree} = 0$ 的節點，將該節點加入排序結果中。

3. 由於當前節點已經從圖中移除並將入排序結果中，該節點所有 out edge 所指向的節點的 $\text{in degree} - 1$ ，如果 - 1 後的節點 $\text{in degree} = 0$ 則將該節點加入 queue 中。

4. 重複步驟 2 和 3 直到 queue 為空，此時排序結果中的節點就是 topological sorting 的結果。

在這道題目中所求的 safe node 正好和 topological sorting 相反，topological sorting 是從 $\text{in degree} = 0$ 的節點開始排序，而 safe node 則是從 $\text{out degree} = 0$ 的節點開始，因此我們可以先將整個圖反轉，再對反轉後的圖進行 topological sorting 即可得到所有的 safe node。

在這個程式碼中會使用 [鏈式前向星（chain forward star）](https://www.bilibili.com/opus/577729382567986697) 這種資料結構來儲存反轉後的圖，這是一種用靜態陣列模擬動態陣列（鄰接表）的儲存方式。

鏈式前向星的優點和缺點：

- 優點：

  - 節點的數量是固定的，因此可以預先分配好空間，避免動態分配記憶體的時間開銷。

  - 適用於稀疏圖，因為只需要儲存邊的資訊，相對於鄰接矩陣來說可以節省空間。

  - 相比 `vector` 鄰接表擁有更好的記憶體使用性能，因為 `vector` 每次擴充時預設會分配兩倍的空間，並且會將 element 複製到新的空間中。

- 缺點：

  - 不適用於稠密圖，因為需要儲存大量的邊，相對於鄰接矩陣來說會浪費空間。

  - 不支援動態添加節點，因為節點的數量是固定的，無法動態添加節點。

主要的變數會有：

- `index`：邊的編號，用來紀錄當前要添加的邊的編號。初始為 0，每次添加一條邊就需要將 $index + 1$ 。

- `he`：head edge，紀錄每個節點的第一條邊。初始為 -1 表示沒有邊，每次添加新的邊 (u, v) 時，節點 `u` 會新增一條邊 (u, v)，因此需要將 `he[u]` 指向新的邊， $he[u] = index$ ，可以和 $index + 1$ 一起寫成 $he[u] = index ++$ 。

- `ne`：next edge，記錄每條邊的下一個邊的編號。每次添加一條邊 (u, v) 時，由於節點 `u` 會新增一條邊 (u, v)，此時的 `he[u]` 會指向這條新的邊，而新的邊則要指向原本 `he[u]` 所指向的邊，因此 $ne[index] = he[u]$ ，需要注意的是要在更新 `he` 之前先更新 `ne` 才會是指向正確的邊。

- `to`：記錄每條邊所指向的節點，每次添加一條邊 (u, v) 時， $to[index] = v$ 。

- `w`：記錄每條邊的權重，每次添加一條邊 (u, v, w) 時， $w[index] = w$ 。

實作程式碼如下：

- 使用 `class` 來實作：

    ```cpp {.line-numbers}
    class ForwardStar {
    private:
        static const int N = 100005; // 頂點數量
        static const int M = 400005; // 邊數量
        int index;                   // 邊的編號
        int he[N];                   // head edge，紀錄每個節點的第一條邊
        int ne[M];                   // next edge，記錄每條邊的下一個邊的編號
        int to[M];                   // 記錄每條邊所指向的節點
        int w[M];                    // 記錄每條邊的權重

    public:
        // 初始化
        ForwardStar() {
            index = 0;
            std::memset(he, -1, sizeof(he));
        }
        // 添加邊
        void add(int u, int v, int w) {
            to[index] = v;
            w[index] = w;
            ne[index] = he[u];
            he[u] = index++;
        }
    };
    ```

- 使用 `struct` 來實作：

    ```cpp {.line-numbers}
    struct edge {
        int ne;
        int to;
        int w;
    } e[M];

    int he[N];
    std::memset(he, -1, sizeof(he));

    int index = 0;
    void add(int u, int v, int w) {
        e[index].next = head[u];
        e[index].to = v;
        e[index].w = w;
        head[u] = index++;
    }
    ```WW

- 遍歷節點 `u` 的所有 out edge：

    ```cpp {.line-numbers}
    // i 是邊的編號（index）
    for (int i = he[u]; i != -1; i = ne[i]) {
        // do something
    }
    ```

#### 程式碼

```cpp {.line-numbers}
class Solution {
  private:
    static const int N = 100005; // 頂點數量
    static const int M = 400005; // 邊數量
    int index;                   // 邊的編號
    int he[N], ne[M], to[M];     // chain forward star

  public:
    Solution() {
        index = 0;
        std::memset(he, -1, sizeof(he));
    }

    // 添加邊
    void add(int u, int v) {
        to[index] = v;
        ne[index] = he[u];
        he[u] = index++;
    }

    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>> &graph) {
        int in_degree[graph.size()];
        std::memset(in_degree, 0, sizeof(in_degree));
        std::queue<int> q;

        // 建立反向圖
        for (int i = 0; i < graph.size(); ++i) {
            for (const int &j : graph[i]) {
                add(j, i);
            }
            // in degree 為反轉前的 out degree 數量
            in_degree[i] = graph[i].size();
            // 將所有 in degree = 0 的節點放入 queue
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }

        // Topological Sorting
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // 將所有相鄰的節點的 in degree 減一
            for (int i = he[u]; i != -1; i = ne[i]) {
                int v = to[i];
                // 若減一後 in degree = 0，則放入 queue
                if (--in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // 將所有 in degree = 0 的節點放入 res
        std::vector<int> res;
        for (int i = 0; i < graph.size(); ++i) {
            if (in_degree[i] == 0)
                res.push_back(i);
        }

        return res;
    }
};
```

[![](https://i.imgur.com/00Xzrnq.png)](https://i.imgur.com/00Xzrnq.png)

#### 複雜度分析

令 $V$ 為圖中節點數量， $E$ 為邊的數量。

- 時間複雜度： $O(V + E)$

    在建立反向圖和 topological sort 時，所有節點都只會被檢查一次，所有邊都只會經過一次。

- 空間複雜度： $O(V + E)$

    需要儲存反轉後的圖，因此空間複雜度為 $O(V + E)$ 。
