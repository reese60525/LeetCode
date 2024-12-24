# <center> [3203. Find Minimum Diameter After Merging Two Trees](https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224155539935.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224155539935.png)

給兩個 undirected tree，`edges1` 和 `edges2` 分別代表兩個 tree 的每個邊，tree 的節點數量分別是 `n`、`m`，邊的數量為 `n-1`、`m-1`，且節點編號從 0 遞增。可以在兩個 tree 中各選一個節點相連，將兩個 tree 合併成一個 tree，求合併後 tree 的最小 diameter。

undirected tree 的 diameter 定義：  

- 在 tree 中任意兩個節點之間的最長路徑的長度。

## 解題思路

### 1. DFS（樹狀 DP）

首先，合併後的 `combine_diameter` 有三種可能的情況：

1. `combine_diameter` = tree1 的 `diameter_1`
2. `combine_diameter` = tree2 的 `diameter_2`
3. 假設 tree1 選 node `a`、tree2 選 node `b`，則 `combine_diameter` = (`a` 到 tree1 任意點的最長路徑長度) + (`b` 到 tree2 任意點的最長路徑長度) + 1（a 到 b 的邊）。

要如何求 tree 的 diameter 呢？  
可以用 DFS 從 node 0 開始遍歷整個 tree，對於某個 node `k` 來說，以 `k` 為 root 且經過 `k` 的最長路徑長度會等於 `k` 所有子樹中**深度**最大的兩個相加。例如：  

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224163921862.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224163921862.png)

node `k` 共有四個子樹，深度分別為 {5, 4, 2, 3}，前二大的深度為 {5, 4}，因此以 `k` 為 root 且經過 `k` 的最長路徑長度為 5 + 4 = 9。  
對於節點 `root`，`root` 的子樹有三個，深度為 {6, 1, 2}，因此經過 `root` 的最長路徑長度為 6 + 2 = 8。  
以這樣的方式遍歷整棵樹，比較所有 node 的最長路徑長度，最大的就是 tree 的 diameter。

知道如何求一棵樹的 diameter 了，接下來要如何求兩棵樹合併後的 diameter 呢？
由前面提到的第三種情況可知，因為要求合併後**最小** diameter，那麼 tree1 和 tree2 相連的節點選擇是重點。要在 tree 中選一個點，使得該點到 tree 中任意點的最長路徑長度是**最短的**，那麼這個點就會在 diameter 的中間點上。由下圖來證明：  

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224172943572.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224172943572.png)

數字表示兩點之間的距離，虛線表示省略顯示兩點之間的樹節點，實線表示真的點對點，因此距離也會是 1，紅色的兩條虛線就是 diameter 路徑。`A` 共有四個子樹，深度分別為 {1001, 99, 98, 97}，而 `B` 有三個子樹，深度分別為 {1000, 50, 101}，diameter 為 `F` 到 `H` 的距離。  
由於 `F` 到 `H` 是整棵樹中任意兩點的最長距離，在 `F` 到 `H` 之間任選一個節點 `X`，`X` 到 `H` 的距離始終都能比 `X` 到 `F` 以外的任何節點還要長，如果有節點 `K` 使 `X` 到 `K` 比 `X` 到 `H` 長，那麼 diameter 就會是 `F` 到 `K` 而不是 `F` 到 `H` 了，因此我們可以將節點不斷往 `F` 靠近，直到 `X` 到 `F`和 `X` 到 `H` 的距離相等或差一時，`X` 到樹中任意點的最長路徑長度就會是最短的。  
以圖中的距離為例子，`F` 到 `H` 的距離是 1101，可以在 `F` 到 `H` 之間找到一點 `X`，使得 `X` 到 `F` 的距離是 551，`X` 到 `H` 的距離是 550，因此 `X` 到樹中任意點的最長路徑長度就是 551。若是 `H` 到 `B` 的距離是 100，則 `F` 到 `H` 的距離是 1100，`X` 到樹中任意點的最長路徑長度就是 550。由此可得以下公式：  

$$
\text{樹中選一節點到任意點的最長路徑的最短長度} = \frac{diameter + 1}{2}
$$

最後我們已經取得三種情況的 diameter，答案就是這三個 diameter 的最大值。

#### 程式碼

```cpp {.line-numbers}
// 將 adj 鄰接圖表創建為全域變數，這樣可以提高效能和降低記憶體使用率
// 如果是在 class 內創建，每次呼叫 class function 都得重新分配和釋放記憶體
const size_t N = 1e5 + 5;
std::vector<std::vector<int>> adj(N);

class Solution {
  public:
    int dfs(const std::vector<std::vector<int>> &adj, int pre, int cur, int &diameter) {
        int max_depth = 0; // 該節點的子樹最大深度
        
        for (const int &next : adj[cur]) {
            if (next == pre) {
                continue;
            }

            int temp = dfs(adj, cur, next, diameter);
            // 計算 diameter，每個子樹的 diameter 是深度最深的兩個分支相加
            diameter = std::max(diameter, max_depth + temp);
            // 更新最大深度
            max_depth = std::max(max_depth, temp);
        }

        // return 當前子樹的最大深度，例如 leaf node 會 return 0 + 1 = 1
        return max_depth + 1;
    }

    int findDiameter(const std::vector<std::vector<int>> &edges) {
        // node 的數量，題目說有 k 條邊，那麼就會有 k+1 個點
        size_t n = edges.size() + 1;
        // 由於 adj 是全域變數，要先清除先前的資料
        for (size_t i = 0; i < n; ++i) {
            adj[i].clear();
        }
        for (auto &edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        int diameter = 0;
        dfs(adj, -1, 0, diameter);
        return diameter;
    }

    int minimumDiameterAfterMerge(std::vector<std::vector<int>> &edges1, std::vector<std::vector<int>> &edges2) {
        int diameter1, diameter2, diameter3;

        diameter1 = findDiameter(edges1);
        diameter2 = findDiameter(edges2);
        diameter3 = (diameter1 + 1) / 2 + (diameter2 + 1) / 2 + 1;

        return std::max({diameter1, diameter2, diameter3});
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224213211604.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224213211604.png)

時間複雜度： $O(n + m)$ ，其中 $n$ 和 $m$ 分別是 `edges1` 和 `edges2` 的節點數。  
空間複雜度： $O(n + m)$ 。

### 2. BFS

對於 diameter 的兩端節點 node `a` 和 node `b` 來說，令 `root` 到 `a` 和 `b` 的最小共同子樹距離為 `d0`（可以是 0），`a` 和 `b` 到最小共同子樹的距離是 `d1` 和 `d2`，假設有一個 node `c` 和 `root` 距離是 `d3`，如果滿足 $d3 > d1 \text{ or } d3 > d2$ ，那麼 `c` 一定能取代 `a` 或是 `b` 成為新的 diameter 的端點，因為這樣的 node `c` 能讓 diameter 的長度更長，這就和 diameter 是 tree 中任意兩端點**最長**的距離這個定義產生了矛盾，因此 `a` 或是 `b` 一定是 `root` 所能到達的最遠 node。所以可以先用 BFS 求出 `root` 的最遠 node `a`，若有多個則任取一個，然後再用 BFS 求 `a` 的最遠 node `b`，`a` 到 `b` 的距離就是 tree 的 diameter。

證明：  

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224211421473.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224211421473.png)  

虛線是省略的樹節點，node `A` 和 `B` 是 tree 的 diameter 的兩端點， $diameter = d1 + d2$ ，假設 $d3 > d1$ ，那麼 $d3 + d0 + d2$ 這個新的距離絕對會大於 $d1 +d2$ ，因此就和 diameter 的定義產生矛盾，可得證 `A` 或 `B` 其中一個一定是 `root` 所能到達的最遠 node。

**node `C` 可以在任何地方，像是 `K` 的子節點或是 `A` 的子節點之類的**

#### 程式碼

```cpp {.line-numbers}
// 將 adj 鄰接圖表創建為全域變數，這樣可以提高效能和降低記憶體使用率
// 如果是在 class 內創建，每次呼叫 class function 都得重新分配和釋放記憶體
const size_t N = 1e5 + 5;
std::bitset<N> visited; // 紀錄是否走訪過
std::vector<std::vector<int>> adj(N);

class Solution {
  public:
    std::pair<int, int> bfs(size_t root) {
        visited.reset();
        std::queue<int> q;
        q.push(root);

        int level = 0, farthest_node;
        while (!q.empty()) {
            int q_size = q.size();
            farthest_node = q.front();
            for (size_t i = 0; i < q_size; ++i) {
                int node = q.front();
                q.pop();
                visited[node] = true;

                // 將所有相鄰節點加入 queue
                for (int &next : adj[node]) {
                    // 如果已經走訪過，則跳過
                    if (visited[next]) {
                        continue;
                    }
                    q.push(next);
                }
            }
            ++level;
        }

        // 返回距離所以 level 要減 1
        return {farthest_node, level - 1};
    }

    int findDiameter(const std::vector<std::vector<int>> &edges) {
        // node 的數量，題目說有 k 條邊，那麼就會有 k+1 個點
        size_t n = edges.size() + 1;
        // 由於 adj 是全域變數，要先清除先前的資料
        for (size_t i = 0; i < n; ++i) {
            adj[i].clear();
        }
        for (auto &edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // 先取得 node 0 的最遠 node a，再以 a 為 root 取得最遠 node b 的距離
        return bfs(bfs(0).first).second;
    }

    int minimumDiameterAfterMerge(std::vector<std::vector<int>> &edges1, std::vector<std::vector<int>> &edges2) {
        int diameter1, diameter2, diameter3;

        diameter1 = findDiameter(edges1);
        diameter2 = findDiameter(edges2);
        diameter3 = (diameter1 + 1) / 2 + (diameter2 + 1) / 2 + 1;

        return std::max({diameter1, diameter2, diameter3});
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224213317419.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224213317419.png)

時間複雜度： $O(n + m)$ ，其中 $n$ 和 $m$ 分別是 `edges1` 和 `edges2` 的節點數。  
空間複雜度： $O(n + m)$ 。

### 3. Topological Sorting（Kahn's Algorithm）

要計算 diameter，可以想像是在剝洋蔥一樣，將最外層的 leaf node 一層一層剝掉，最後會剩下一個或是兩個 node，剩下的 node 就是 tree 的中心點，假設共剝掉 `k` 層 leaf node，如果剩下一個 node，tree 的 diameter 就是 $2 \cdot k$ ，如果剩下兩個 node，因為這兩個 node 也會相連成一條邊，所以 diameter 就會是 $2 \cdot k + 1$ 。令 `n` 是剩下的 node 數量，可得到公式： $diameter = 2 \cdot k + (n - 1)$
。  
我們可以用 Kahn's Algorithm 來完成，計算每個 node 的 degree，將 degree 為 1 的 node 加入到 queue 中，然後將其取出，遍歷和這些 leaf node 相連的 node，將其 degree 減 1，如果 degree 變成 1 表示這個 node 也變成 leaf node，要加入 queue 中，重複這個過程直到節點數量小於 2，就能計算出 diameter。

#### 程式碼

```cpp {.line-numbers}
// 將 adj 鄰接圖表創建為全域變數，這樣可以提高效能和降低記憶體使用率
// 如果是在 class 內創建，每次呼叫 class function 都得重新分配和釋放記憶體
const size_t N = 1e5 + 5;
std::vector<int> degree(N); // 紀錄每個 node 的 degree
std::vector<std::vector<int>> adj(N);

class Solution {
  public:
    int KahnAlgorithm(size_t n) {
        std::queue<int> q;
        // 將所有 leaf node 加入 queue
        for (size_t i = 0; i < n; ++i) {
            if (degree[i] == 1) {
                q.push(i);
            }
        }

        int level = 0; // 紀錄共幾層
        // 最後會留下一個或兩個 node
        while (n > 1) {
            int q_size = q.size();
            n -= q_size;
            for (size_t i = 0; i < q_size; ++i) {
                int leaf_node = q.front();
                q.pop();

                // 將新的 leaf node 加入 queue
                for (int &node : adj[leaf_node]) {
                    if (--degree[node] == 1) {
                        q.push(node);
                    }
                }
            }

            ++level;
        }

        return level * 2 + n - 1;
    }

    int findDiameter(const std::vector<std::vector<int>> &edges) {
        // node 的數量，題目說有 k 條邊，那麼就會有 k+1 個點
        size_t n = edges.size() + 1;
        // 由於 adj 和 degree 是全域變數，要先清除先前的資料
        for (size_t i = 0; i < n; ++i) {
            adj[i].clear();
            degree[i] = 0;
        }
        for (auto &edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
            ++degree[edge[0]];
            ++degree[edge[1]];
        }

        return KahnAlgorithm(n);
    }

    int minimumDiameterAfterMerge(std::vector<std::vector<int>> &edges1, std::vector<std::vector<int>> &edges2) {
        int diameter1, diameter2, diameter3;

        diameter1 = findDiameter(edges1);
        diameter2 = findDiameter(edges2);
        diameter3 = (diameter1 + 1) / 2 + (diameter2 + 1) / 2 + 1;

        return std::max({diameter1, diameter2, diameter3});
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224214841319.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241224214841319.png)

時間複雜度： $O(n + m)$ ，其中 $n$ 和 $m$ 分別是 `edges1` 和 `edges2` 的節點數。  
空間複雜度： $O(n + m)$ 。
