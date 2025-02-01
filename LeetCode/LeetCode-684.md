# <center> [684. Redundant Connection](https://leetcode.com/problems/redundant-connection/description/) </center>

## 題目敘述

[![](https://i.imgur.com/2kz6Wha.png)](https://i.imgur.com/2kz6Wha.png)

給一個整數陣列 `edges` 表示一個有 `n` 個節點的無向圖的所有邊， $edges[i] = [a, b]$ 表示 $a$ 和 $b$ 之間有一條邊，請找出圖中一條邊將其刪去後可以得到一個有 `n` 個節點的 **樹**，若有多種答案則刪除 **`edges` 中最後出現的那條邊**。

- 樹可以看做為 **無環** 的 **無向** 圖。

- `edges` 中不會有重複的邊，也就是不會同時存在 `[a, b]` 和 `[b, a]`。

- `edges` 組成的圖是 **連通** 的，也就是只會有一個連通分量。

## 解題思路

### Disjoint Set Union（DSU）

根據題目敘述，我們可以得知該無向圖正好會有一個環，將環中任一條邊刪除後就能得到一個 `n` 個節點的樹，因此可以用 DSU 將所有邊進行分類，環中所有的邊必定會屬於同個集合中。

遍歷 `edges`，當某條邊 `[a, b]` 的節點 `a` 和 `b` 都屬於同個集合時表示這條邊就是環邊，並且也會是 `edges` 中最後一條環邊，因為只有最後一條環邊的兩節點才會在合併集合前就已經是同個集合了。

#### 程式碼

```cpp {.line-numbers}
class DSU {
  private:
    int root[1005]; // 紀錄每個節點的 root
    int rank[1005]; // 紀錄每個 root 的樹高

  public:
    DSU() {
        for (int i = 0; i < 1005; ++i) {
            root[i] = i;
        }
        std::memset(rank, 0, sizeof(rank));
    }

    // 查找 root，並將路徑壓縮
    inline int find(int x) {
        return x == root[x] ? x : root[x] = find(root[x]);
    }

    // 將兩個集合進行合併（by rank）
    void connect(int px, int py) {
        if (rank[px] > rank[py]) {
            root[py] = px;
        }
        else if (rank[px] < rank[py]) {
            root[px] = py;
        }
        else {
            root[py] = px;
            ++rank[px];
        }
    }

    // 檢查兩節點是否為同集合，是的話表示這條邊會構成環
    bool isUnion(int x, int y) {
        int px = find(x), py = find(y);
        if (px != py) {
            connect(px, py);
            return false;
        }
        return true;
    }
};

class Solution {
  public:
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>> &edges) {
        DSU dsu;

        // 將所有邊加到 dsu 中並檢查是否為環邊
        for (auto &edge : edges) {
            int a = edge[0], b = edge[1];
            if (dsu.isUnion(a, b)) {
                return {a, b};
            }
        }

        return {};
    }
};
```

[![](https://i.imgur.com/7jnF2SA.png)](https://i.imgur.com/7jnF2SA.png)

#### 時間複雜度

令 $n$ 為節點數。

- 時間複雜度： $O(n \cdot \alpha(n))$

    由於這題的無向圖在刪除一條邊後會變成樹，而一個有 $n$ 個節點的樹會有 $n-1$ 條邊，因此 `edges` 共有 $n$ 個節點和 $n$ 條邊。

    對每條邊進行 `connect` 的操作需要 $O(\alpha (n))$ 的時間，整個 code 為 $O(n \cdot \alpha(n))$ 。

- 空間複雜度： $O(n)$

    紀錄每個節點的 `root` 和 `rank` 需要 $O(n)$ 的空間。
