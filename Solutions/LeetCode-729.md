# <center> [729. My Calendar I](https://leetcode.com/problems/my-calendar-i/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501091959149.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501091959149.png)

給一個 `MyCalendar` class，裡面有 `book(int start, int end)` function，用來新增一個時間區間，如果新增的時間區間與已經存在的時間區間有重疊，則回傳 false，否則回傳 true，請完成這個 class。

- 時間區間為 `[start, end)` ，也就是說，`start` 是包含在時間區間內，而 `end` 則不包含在時間區間內。

## 解題思路

### 1. Binary Search

對於新輸入進來的時間區間 `[s_i, e_i)`，如果任意的已存在的時間區間 `[s_k, e_k)` 都沒有和其有重疊，表示 $e_i \leq s_k$ 或是 $s_i \geq e_k$ ，因此可以將所有時間區間存放到 binary search tree 中，將要新增的時間區間和 binary search tree 中的時間區間做比較，若都沒有重疊，則將其新增到 binary search tree 中並 return true，反之 return false。

#### 程式碼

```cpp {.line-numbers}
struct Node {
    int start, end;
    Node *left, *right;
    Node(int st, int ed) : start(st), end(ed), left(nullptr), right(nullptr) {};
};

class MyCalendar {
  private:
    Node *root;

  public:
    // 初始化 root 為 nullptr
    MyCalendar() : root(nullptr) {}

    // 搜尋 binary search tree
    // Node *&cur 是傳入資料型態為 Node* 的 reference，而不是 temp value
    bool dfs(int st, int ed, Node *&cur) {
        // 在 tree 沒有任何區間跟搜尋的區間重疊
        // 這樣修改 nullptr 能起作用是因為 cur 是 cur->left 或 cur->right 的 reference
        if (cur == nullptr) {
            cur = new Node(st, ed);
            return true;
        }

        // 繼續檢查其餘區間
        if (ed <= cur->start) {
            return dfs(st, ed, cur->left);
        }
        else if (st >= cur->end) {
            return dfs(st, ed, cur->right);
        }

        // 搜尋的區間跟 tree 中某個區間有重疊
        return false;
    }

    bool book(int startTime, int endTime) {
        return dfs(startTime, endTime, root);
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501092024808.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501092024808.png)

#### 複雜度分析

令 $n$ 為目前 binary search tree 中的節點數量。

- 時間複雜度： $O(n \log n)$

- 空間複雜度： $O(n)$

---

除了手寫一個 binary search tree 外，也可以使用 C++ 內建的 `std::set` 來實作。

找出 `std::set` 中第一個結束時間大於等於 `endTime` 的時間區段 `it`，如果 `std::set` 為空，或是 `it` 的前一個區間的結束時間小於等於 `startTime`，則可以插入。

#### 程式碼

```cpp {.line-numbers}
class MyCalendar {
  private:
    std::set<std::pair<int, int>> event;

  public:
    MyCalendar() {}

    bool book(int startTime, int endTime) {
        // 使用 lower_bound 找到第一個大於等於 endTime 的 iterator
        const auto it = event.lower_bound({endTime, 0});
        // 如果 event 為空，或是 it 的前一個區間的 endTime 小於等於 startTime，則可以插入
        if (it == event.begin() || startTime >= prev(it)->second) {
            event.emplace(startTime, endTime);
            return true;
        }
        return false;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501092031613.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501092031613.png)

#### 複雜度分析

令 $n$ 為目前 binary search tree 中的節點數量。

- 時間複雜度： $O(n \log n)$

- 空間複雜度： $O(n)$
