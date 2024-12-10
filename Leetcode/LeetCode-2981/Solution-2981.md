# <center> [LeetCode - 2981. Find Longest Special Substring That Occurs Thrice I](https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412101114767.png)]((https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412101114767.png))

給一個只有小寫英文字母的字串 `s`，找出至少出現三次的最長 `special` substring 的長度，如果找不到則 return -1。

special substring 的定義：

- 字串中只包含同樣的字元，例如 "a"、"aaa"、"bbbbbbbb"。

e.g.

1. s = "aaaa"  
   - "a" 出現四次，長度為 1。
   - "aa" 出現三次，長度為 2。
   - "aaa" 出現兩次，長度為 3。
   - "aaaa" 出現一次，長度為 4。

    因此至少出現三次的最長 `special` substring 是 "aa"，長度為 2。

2. s = "abcd"  
   因為沒有任何 `special` substring 出現三次以上，所以 return -1。

3. s = "abcaba"  
   - "a" 出現三次，長度為 1。

   因此至少出現三次的最長 `special` substring 是 "a"，長度為 1。

## 解題思路

### 1. Sliding Window and Hash Map

對於長度為 $n$ 的 `special` substring，可以發現該 `special` substring 可以構成同樣字母且長度為 $[1, n]$ 的 `special` substring，以 `s` = "aaaa" 為例，"a" 出現四次、"aa" 出現三次、"aaa" 出現兩次、"aaaa" 出現一次，可以發現這是遞減的。  

利用這個特性遍歷 `s` 用 `sliding window` 的方式將其切成多個 `special` substring，對於每個 `special` substring 將其所有可能的 `special` substring 長度的次數存進 `hash map` 中，同時從 `hash map` 中確認當前長度的 `special` substring 是否出現三次以上，如果是則將其和當前的答案 `res` 做比較取較大值。

e.g.

s = "aaabbaaaa"，`res` 初始化為 -1。

   1. 首先將 `s` 切成 {"aaa", "bb", "aaaa"}  
   2. 對於每個 `special` substring 將其所有可能的 `special` string 長度的次數存進 `hash map` 中，同時確認該字母當前長度的 `special` string 是否出現三次以上，如果是則將其和當前的答案 `res` 做比較取較大值。  
      - "aaa" 可以構成 "a" 出現三次、"aa" 出現兩次、"aaa" 出現一次。  
        - "a" 出現三次，長度為 1，`res` 更新為 1。
      - "bb" 可以構成 "b" 出現兩次、"bb" 出現一次。  
      - "aaaa" 可以構成 "a" 出現四次、"aa" 出現三次、"aaa" 出現兩次、"aaaa" 出現一次。  
        - "aa" 共出現五次，長度為 2，`res` 更新為 2。
        - "aaa" 共出現三次，長度為 3，`res` 更新為 3。
   3. 遍歷完 `s` 後，`res` 為 3，return 3。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    int maximumLength(std::string s) {
        int res = -1, len = 0;  // len 紀錄當前 special substring 的長度
        int freq[26][50] = {0}; // 紀錄每種字母每個 special substring 出現的次數

        for (int i = 0; i < s.size(); i++) {
            ++len;

            // 到字串末端 或是 當前字母與下一個字母不同時，代表當前 special substring 結束
            if (i == s.size() - 1 || s[i] != s[i + 1]) {
                // 由該 special substring 所能組成的 substring 也是 special substring
                // 將每種長度的 special substring 累加
                for (int j = 0; j < len; ++j) {
                    freq[s[i] - 'a'][j] += len - j;
                    // 如果該字母當前長度的 special substring 出現次數大於等於 3 則去跟 res 比較
                    if (freq[s[i] - 'a'][j] >= 3) {
                        res = std::max(res, j + 1);
                    }
                }
                len = 0;
            }
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210134516818.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210134516818.png)

時間複雜度： $O(n)$ ，其中 $n$ 為字串 `s` 的長度。  
空間複雜度： $O(1)$ ，因為 `freq` 的大小固定為 $26 \times 50$，是常量。  

### 2. Sliding Window and Priority Queue

假設字母 'a' 分別有最大長度為 {a[0], a[1], a[2]} 的 `special` substring， $a[0] \geq a[1] \geq a[2]$ ，可以觀察到以下規則:  

1. 對於長度最長的 `a[0]`  
   - 可以切出出現三次且長度為 $a[0] -2$ 的 `special` substring。  
2. 對於長度最長的 `a[0]` 和第二長的 `a[1]`  
   - 如果 $a[0] = a[1]$，可以切出出現四次且長度為 $a[0] -1$ 的 `special` substring。  
   - 如果 $a[0] > a[1]$，可以切出出現超過三次且長度為 $a[1]$ 的 `special` substring。  
   - 可以將這兩種情況合併為 $min(a[0]-1, a[1])$ 。  
3. 對於長度最長的 `a[0]`、第二長的 `a[1]` 和第三長的 `a[2]`  
   - 這三種長度可以切出出現超過三次且長度為 $a[2]$ 的 `special` substring。  

因此對於以上所有情況可以總結為字母 'a' 的最大長度 `special` substring 為 $max(a[0]-2, min(a[0]-1, a[1]), a[2])$ 。

實作上，遍歷 `s`，將當前字母的 `special` substring 長度加入 min heap 的 `priority queue` 中，並且維護 `priority queue` 的大小為 3。接著遍歷 `priority queue`，若不為空，將 `priority queue` 中的 element 取出，算出該字母的最長 `special` substring 並且將其和當前的答案 `res` 做比較取較大值。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    int maximumLength(std::string s) {
        int len = 0; // 紀錄當前 special substring 的長度
        // 紀錄每種字母的前三長的 special substring 長度
        std::vector<std::priority_queue<int, std::vector<int>, std::greater<int>>> freq(26);

        // 遍歷 s，將每個字元的 special substring 的每種長度出現的次數記錄到 freq 中
        for (int i = 0; i < s.size(); ++i) {
            ++len;

            // 遍歷到最後一個字元 或是 當前字元和下一個字元不同時，代表一個 special substring 結束
            if (i == s.size() - 1 || s[i] != s[i + 1]) {
                freq[s[i] - 'a'].push(len);

                // 維護 pq 的 size 為 3
                if (freq[s[i] - 'a'].size() > 3) {
                    freq[s[i] - 'a'].pop();
                }

                len = 0;
            }
        }

        int res = 0;
        // 遍歷 freq，找出最長的 special substring 的長度
        for (auto &pq : freq) {
            // 如果 pq 是空的，代表沒有這種字母的 special substring，跳過
            if (pq.empty()) {
                continue;
            }

            // 如果 pq element 數量小於 3，先 push 0 直到有三個
            // 這樣的話就算只有一種長度的 special substring 也能進行後續的長度計算
            // 而不用一堆 if 來判斷修改怎麼計算長度
            while (pq.size() < 3) {
                pq.push(0);
            }

            // pq 是 min heap，依序 push 出最小、中間、最大的長度
            // 由於 len 是從 index = 2 往前填，所以 len[0] 是最小的，len[2] 是最大的
            int len[3] = {0};
            while (!pq.empty()) {
                len[pq.size() - 1] = pq.top();
                pq.pop();
            }

            // 開始進行比較
            res = std::max({res, (len[0] - 2), std::min(len[0] - 1, len[1]), len[2]});
        }

        // res = 0 代表沒有任何 special substring，回傳 -1
        return res == 0 ? -1 : res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210145847968.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210145847968.png)

時間複雜度： $O(n)$ ，其中 $n$ 為字串 `s` 的長度，`pq` 的大小維護在 3 以內，排序為常量時間操作。  
空間複雜度： $O(1)$ ，因為 `freq` 的大小最多為 $26 \times 3$，是常量。

### 3. Sliding Window and Binary Search

令 $n$ 為 `s` 的長度，對長度區間 $[1, n]$ 進行 `binary search`，對於每種長度可以使用 `sliding window`來找出現超過三次的 `special` substring。`binary search` 結束後 `l - 1` 就是最長的 `special` substring 的長度。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    // 搜索長度為 k 的 special substring
    bool findSpecialString(std::string &s, int k) {
        // freq 紀錄當前字母長度為 k 的 special substring 出現次數
        int freq[26] = {0}, len = 0;
        for (int i = 0; i < s.size(); ++i) {
            ++len;

            // 若長度大於等於 k 則出現次數 +1
            if (len >= k) {
                ++freq[s[i] - 'a'];
            }
            // 該字母長度 k 的 special substring 出現次數為 3 則回傳 true 表示找到
            if (freq[s[i] - 'a'] == 3) {
                return true;
            }

            // 遍歷 s 到末端 或是 當前字母與下一個字母不同，表示 special substring 結束
            if (i == s.size() - 1 || s[i] != s[i + 1]) {
                len = 0;
            }
        }

        // 遍歷完 s 沒有找到出現三次長度為 k 的 special substring 則回傳 false
        return false;
    }

    int maximumLength(std::string s) {
        int l = 1, r = s.size();

        // binary search 找最長 special substring 長度
        while (l <= r) {
            // mid 為當前要搜索的 special substring 長度
            int mid = l + (r - l) / 2;

            // 若存在長度為 mid 的 special substring 則繼續往右搜索
            if (findSpecialString(s, mid)) {
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }

        // l-1 為最長 special substring 長度，如果是 0 表示沒有出現超過三次的 special substring 則回傳 -1
        return l - 1 == 0 ? -1 : l - 1;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210153801342.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210153801342.png)

時間複雜度： $O(n \log n)$ ，其中 $n$ 為字串 `s` 的長度，`binary search` 的時間複雜度為 $O(\log n)$，`sliding window` 的時間複雜度為 $O(n)$。  
空間複雜度： $O(1)$ ，因為 `freq` 的大小最多為 $26$，是常量。
