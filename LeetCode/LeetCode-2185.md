# <center> [2185. Counting Words With a Given Prefix](https://leetcode.com/problems/counting-words-with-a-given-prefix/description/) </center>

## 題目敘述

[![](https://i.imgur.com/zVWDSpQ.png)](https://i.imgur.com/zVWDSpQ.png)

給一個字串陣列 `words` 和一個字串 `pref`，回傳 `words` 中以 `pref` 為前綴的字串數量。

## 解題思路

### 1. Brute Force

一個一個去比對。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int prefixCount(std::vector<std::string> &words, std::string pref) {
        int res = 0;
        for (std::string &word : words) {
            if(word.find(pref) == 0) {
                ++res;
            }
        }

        return res;
    }
};
```

[![](https://i.imgur.com/iellycr.png)](https://i.imgur.com/iellycr.png)

#### 複雜度分析

令 $n$ 為 `words` 的長度， $m$ 為 `pref` 的長度。

- 時間複雜度： $O(n \cdot m)$

- 空間複雜度： $O(1)$

### 2. Trie

使用 `Trie` 來儲存 `words` 中的字串，並在插入時記錄每個節點的出現次數。最後，從根節點開始，遍歷 `pref` 中的每個字元，並在 `Trie` 中查找對應的節點，該節點的出現次數即為以 `pref` 為前綴的字串數量。

用 `Trie` 來做的好處是當有多個 `pref`，可以直接查找每個 `pref` 而不用每次都要重新計算，不用重建 `Trie`。

#### 程式碼

```cpp {.line-numbers}
class Trie {
  private:
    int node_cnt = 0;
    Trie *next[26] = {nullptr};

  public:
    // 插入字串
    void insert(std::string &s) {
        Trie *cur = this;
        for (char &c : s) {
            if (cur->next[c - 'a'] == nullptr) {
                cur->next[c - 'a'] = new Trie();
            }
            cur = cur->next[c - 'a'];
            ++cur->node_cnt;
        }
    }

    // 返回以 s 為 prefix 的字串數量
    int search(std::string &s) {
        Trie *cur = this;

        for (char &c : s) {
            if (cur->next[c - 'a'] == nullptr) {
                return 0;
            }
            cur = cur->next[c - 'a'];
        }

        return cur->node_cnt;
    }
};

class Solution {
  public:
    int prefixCount(std::vector<std::string> &words, std::string pref) {
        Trie *root = new Trie();
        for (std::string &word : words) {
            root->insert(word);
        }

        return root->search(pref);
    }
};
```

[![](https://i.imgur.com/0EgxMbA.png)](https://i.imgur.com/0EgxMbA.png)

#### 複雜度分析

令 $n$ 為 `words` 的長度， $m$ 為 `pref` 的長度， $l$ 為 `words` 中字串的最長長度。

- 時間複雜度： $O(n \cdot l + m)$

- 空間複雜度： $O(n \cdot l)$
