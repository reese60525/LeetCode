# <center> [407. Trapping Rain Water II](https://leetcode.com/problems/trapping-rain-water-ii/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501191635725.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501191635725.png)

給一個 `m x n` 的二維整數陣列 `heightMap`，`heightMap[i][j]` 代表每個柱子的高度，求該矩陣可以裝多少雨水。

## 解題思路

對於[一維的接雨水問題](https://leetcode.com/problems/trapping-rain-water/description/)，我們可以透過查找每個柱子左右兩邊最高的柱子，並且取兩者之間較低的那個來計算出該柱子能接住多少雨水。那麼對於二維的矩陣也能透過找出每個柱子四個方向各自最高的柱子，並且取四者之間最低的柱子來計算出能接住多少雨水嗎？答案是不行的，因為在二維的情況下，雨水可以流通的路徑並不僅限於單純的四個直線方向。

用以下例子來說明：

```text
0 0 7 0 0
0 0 3 0 0
4 1 3 5 2
0 0 2 0 0
0 0 4 0 0
```

對於上面這個矩陣，以高度為 3 的柱子 (2, 2) 來看，其四個方向最高的柱子分別為 7、4、4、5，以一維的思路來看能接住 min(7, 4, 4, 5) - 3 = 1 單位的雨水，但實際上該柱子上的雨水能以這樣的路徑來流動 (2, 2) -> (3, 2) -> (3, 3)，這樣子就會把所有雨水都流光了，能接住的雨水為 0 單位。

```text
9 9 9 9 9 9 9 9 8 9 9
9 0 0 0 0 0 0 0 0 0 9
9 0 0 0 0 0 0 0 0 0 9
9 0 0 0 1 0 0 0 0 0 9
9 0 0 0 0 0 0 0 0 0 9
9 9 9 9 9 9 9 9 9 9 9 
```

同樣地，對於上圖這個矩陣，在高度為 1 的柱子 (3, 4) 的四個方向最高柱子分別為 9、9、9、9，看似能夠接住 9 - 1 = 8 單位的雨水，但實際上該柱子上的雨水能以這樣的路徑來流動 (3, 4) -> (2, 4) -> (1, 4) -> (1, 5) -> (1, 6) -> (1, 7) -> (1, 8) -> (0, 8)，8 單位的水會有 1 單位從高度為 8 的柱子 (0, 8) 流走，因此正確的雨水量應該是 8 - 1 = 7 單位。

### 1. Dijkstra's Algorithm and Priority Queue

首先思考一個問題，一個柱子能接住雨水要有什麼條件呢？

1. 該柱子不能是矩陣的最外圍柱子。
2. 該柱子的高度要**小於**其四周柱子**接完雨水後**的高度。

根據木桶原理，能接到雨水的高度取決於該容器中最短的那個木板，也就是由矩陣的邊界中最短的柱子所決定。

用下圖來解釋：

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501191645770.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501191645770.png)

矩陣初始的邊界為最外圍的柱子，而這之中最短的柱子決定了該矩陣能接住多少雨水，從高度為 4 的柱子出發，查找四周不是邊界的柱子，可以發現一個高度為 3 的柱子，並且該柱子的高度小於 4，因此可以接住雨水，接完雨水後的高度會變成 4，此時將該柱子加入至邊界中，而柱子 (0, 2) 則從邊界中移除，以此來更新邊界，縮小範圍。

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501191702621.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501191702621.png)

接著繼續從邊界中選擇最短的柱子，從高度為 4 的柱子出發，檢查四周柱子，可以發現有高度為 1 和高度為 4 的柱子還沒接雨水，計算接完雨水後的高度，將其加入邊界中，並將柱子 (1, 2) 從邊界中移除。

最終我們就能計算出矩陣能夠承接的雨水總量。

---

讓我們換個思考方式，為何說這題是一種 `Dijkstra's Algorithm` 的問題呢？

首先定義 `max_height` 為柱子 (x, y) 到邊界的路徑中最高的柱子高度，而這道問題的核心就是在求 **從柱子 (x, y) 到邊界的所有路徑的 `max_height` 中的最小值是多少**，這個最小值和柱子 (x, y) 的高度差就會是該柱子能接住的雨水體積。

原本 `Dijkstra's Algorithm` 是用來計算最短路徑問題，而這題求的是 `max_height` 的最小值，所以要將 `Dijkstra's Algorithm` 變形。對於從柱子 (x, y) 出發到邊界的所有路徑，可以將其看成從邊界到柱子 (x, y) 的所有路徑，並且在這些邊界中我們可以選擇高度最低的邊界柱子來做為起點，這樣就能將從多個邊界到柱子 (x, y) 的多源問題轉換成單源問題。

和尋找最短路徑的 `Dijkstra's Algorithm` 類似，原本尋找最短路徑需要保證從 `priority queue` 取出的路徑是最終的最短路徑，同樣地在這題中需要保證從 `priority queue` 取出的柱子高度（接完雨水後）是最終高度，那麼就能保證該做法的正確性。

首先，矩陣初始的邊界一定無法接雨水，所以能將這些邊界柱子先加入至 `priority queue` 中，接著要考慮如何保證從 `priority queue` 取出的柱子高度已經是最終高度來保證演算法的正確性，而根據 「木桶原理」，對於柱子 (x, y) 來說，其接住雨水後的最終高度取決於其四周柱子中接完雨水後的高度最小的柱子，因此可以將 `priority queue` 以**高度**由小到大排序，每次取出都是高度最小的邊界，那麼就能保證該取出的柱子其四周柱子在更新接完雨水後的高度都是四周柱子中最終高度最小的那個，也就能保證該做法的正確性。

以上兩種思考方式的作法都相同，整體演算法流程如下：

1. 將矩陣的初始邊界加入至 `min heap` 的 `priority queue` 中，並將該柱子標記為 `visited`。

2. 從 `priority queue` 取出最短的柱子，檢查四周的柱子，計算未訪問過的柱子能接住的雨水體積，然後更新柱子高度為接雨水後的高度，若是原本高度就比接雨水後的高度還高則不變，將更新高度後的柱子加入至 `priority queue` 中，並把該柱子標記為 `visited`。

3. 重複步驟 2 直到 `priority queue` 為空，最終就能計算出答案。

#### 程式碼

```cpp {.line-numbers}

typedef std::array<int, 3> INT3; // {x, y, height}

class Solution {
  public:
    int trapRainWater(std::vector<std::vector<int>> &heightMap) {
        int r = heightMap.size(), c = heightMap[0].size();
        // pq 存放當前的邊界，將 pq 中的邊界以高度由小排到大
        auto cmp = [](const INT3 &a, const INT3 &b) {
            return a[2] > b[2];
        };
        std::priority_queue<INT3, std::vector<INT3>, decltype(cmp)> pq(cmp);
        // 紀錄已經走過的節點
        bool vis[r][c];
        std::memset(vis, 0, sizeof(vis));

        // 將矩陣初始的邊界加入至 pq
        for (int i = 0; i < c; ++i) {
            pq.push({0, i, heightMap[0][i]});
            pq.push({r - 1, i, heightMap[r - 1][i]});
            vis[0][i] = vis[r - 1][i] = true;
        }
        for (int i = 1; i < r - 1; ++i) {
            pq.push({i, 0, heightMap[i][0]});
            pq.push({i, c - 1, heightMap[i][c - 1]});
            vis[i][0] = vis[i][c - 1] = true;
        }

        // 從 pq 中取出柱子，並更新邊界和計算能夠儲存的雨水總量
        int res = 0;
        int dirs[5] = {-1, 0, 1, 0, -1}; // 上、右、下、左
        while (!pq.empty()) {
            auto [x, y, height] = pq.top();
            pq.pop();

            // 檢查四周的柱子
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i], ny = y + dirs[i + 1];
                // 超出邊界或是拜訪過的就跳過
                if (nx < 0 || nx >= r || ny < 0 || ny >= c || vis[nx][ny]) {
                    continue;
                }

                int nheight = std::max(height, heightMap[nx][ny]); // 計算接雨水後的高度
                res += std::max(0, height - heightMap[nx][ny]);    // 計算該柱子能接多少雨水
                pq.push({nx, ny, nheight});                        // 將該柱子當作新的邊界加入至 pq
                vis[nx][ny] = true;                                // 標記該柱子已經拜訪過
            }
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501191720718.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501191720718.png)

時間複雜度： $O(m \cdot n \times \log (m \cdot n))$  
其中 $m$ 和 $n$ 分別為矩陣的 `row` 和 `column` 大小，共有 $O(m \cdot n)$ 個柱子要處理，維護 `priority queue` 的時間複雜度為 $O(\log(m \cdot n))$，因此總時間複雜度為 $O(m \cdot n \times \log (m \cdot n))$ 。

空間複雜度： $O(m \cdot n)$

---

如果要進一步提升時間和空間效率，可以將柱子的資訊打包成一個 integer，並且刪除 `vis` 陣列，直接將走過的柱子的高度改為 -1 表示已經走過。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  private:
    // 將柱子的數據打包成整數來儲存
    static inline int pack(const int &height, const int &x, const int &y) {
        return (height << 16) | (x << 8) | y;
    }
    // 將柱子數據解包
    static inline std::array<int, 3> unpack(const int &packed) {
        return {packed >> 16, (packed >> 8) & 0xff, packed & 0xff};
    }

  public:
    int trapRainWater(std::vector<std::vector<int>> &heightMap) {
        int r = heightMap.size(), c = heightMap[0].size();
        // pq 存放當前的邊界，將 pq 中的邊界以高度由小排到大
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

        // 將矩陣初始的邊界加入至 pq
        for (int i = 0; i < c; ++i) {
            pq.push(pack(heightMap[0][i], 0, i));
            pq.push(pack(heightMap[r - 1][i], r - 1, i));
            heightMap[0][i] = heightMap[r - 1][i] = -1; // 將拜訪過的柱子標記為 -1
        }
        for (int i = 1; i < r - 1; ++i) {
            pq.push(pack(heightMap[i][0], i, 0));
            pq.push(pack(heightMap[i][c - 1], i, c - 1));
            heightMap[i][0] = heightMap[i][c - 1] = -1; // 將拜訪過的柱子標記為 -1
        }

        // 從 pq 中取出柱子，並更新邊界和計算能夠儲存的雨水總量
        int res = 0;
        int dirs[5] = {-1, 0, 1, 0, -1}; // 上、右、下、左
        while (!pq.empty()) {
            auto [height, x, y] = unpack(pq.top());
            pq.pop();

            // 檢查四周的柱子
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i], ny = y + dirs[i + 1];
                // 超出邊界或是拜訪過的就跳過
                if (nx < 0 || nx >= r || ny < 0 || ny >= c || heightMap[nx][ny] == -1) {
                    continue;
                }

                int nheight = std::max(height, heightMap[nx][ny]); // 計算接雨水後的高度
                res += std::max(0, height - heightMap[nx][ny]);    // 計算該柱子能接多少雨水
                pq.push(pack(nheight, nx, ny));                    // 將該柱子當作新的邊界加入至 pq
                heightMap[nx][ny] = -1;                            // 標記該柱子已經拜訪過
            }
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501191746147.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501191746147.png)

時間複雜度： $O(m \cdot n \times \log (m \cdot n))$

空間複雜度： $O(m \cdot n)$
