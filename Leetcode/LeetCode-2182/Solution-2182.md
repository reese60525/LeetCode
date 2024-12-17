# <center> [LeetCode - 2182. Construct String With Repeat Limit](https://leetcode.com/problems/construct-string-with-repeat-limit/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241217133236208.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241217133236208.png)

給一個只有小寫英文字母的 string `s` 和一個 integer `repeatLimit`，請使用 `s` 中的字元來構造一個新的 string，並且滿足以下條件：  

1. 相同的字元最多只能連續相鄰 `repeatLimit` 次。
2. 新的 string 是所有可構成的 string 中 **字典序最大** 的。
3. 不用把 `s` 中的所有字元都用完。

e.g.

1. `s` = "cczazcc"，`repeatLimit` = 3  
    - 要構成 **最大字典序** 的 string，從 'z' 開始，'z' 是當前 `s` 中字典序最大的字元，接著是 'c'，最後是 'a'。  
    - `res` = "zz"，'z' 用完了換下個字元。  
    - `res` = "zzccc"，'c' 最多只能連續相鄰 3 次。  
    - `res` = "zzccca"，加入當前次大字元 'a'。  
    - `res` = "zzcccac"，所有字元都用完了，結束。  
2. `s` = "aababab"，repeatLimit = 2  
    - 要構成 **最大字典序** 的 string，從 'b' 開始，'b' 是當前 `s` 中字典序最大的字元，接著是 'a'。  
    - `res` = "bb"，'b' 最多只能連續相鄰 2 次。  
    - `res` = "bba"，加入當前次大字元 'a'。  
    - `res` = "bbab"，'b' 用完了換下個字元。  
    - `res` = "bbabaa"，'a' 最多只能連續相鄰 2 次。  
    - 沒有次大字元了，結束，res = "bbabba"。  

## 解題思路

### 1. Greedy and Hash Map

由於要構成 **最大字典序** 的 string，所以可以用 `greedy` 從當前 `s` 中字典序最大的字元開始。用 `hash map` 來記錄每個字元出現的次數，接著用兩個指標 `p1` and `p2` 分別代表當前最大字元和次大字元，遍歷 `hash map` （小寫英文字母頻率表，size 為 26）來構造新的 string，如果 `p1` 出現次數大於 `repeatLimit`，`res` 加入 `repeatLimit` 次的 `p1`，並加入 1 個 `p2`，若 `p2` 用完則結束迴圈。如果 `p1` 出現次數小於等於 `repeatLimit`，將所有 `p1` 加入 `res` 中，`p1` 變為 `p2`，`p2` 變為下一個次大字元。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::string repeatLimitedString(std::string s, int repeatLimit) {
        // 紀錄字母的出現次數
        int freq[26] = {0};
        for (char c : s) {
            ++freq[c - 'a'];
        }

        int cur = 25, next = 25; // cur: 當前最大字母，next: 當前次大字母
        s.clear();               // 使用原先題目給的 s 來存放答案
        while (cur >= 0) {
            // 找出當前最大字母與次大字母
            if (freq[cur] == 0) {
                --cur;
                continue;
            }
            if (next >= 0 && (next >= cur || freq[next] == 0)) {
                --next;
                continue;
            }

            // 將當前最大字母加入 s 中
            int cnt = std::min(freq[cur], repeatLimit); // 最多只能連續 repeatLimit 次，若不足則全部加入
            s.append(cnt, ('a' + cur));
            freq[cur] -= cnt;

            // 如果當前最大字母用完，則將其變成次大字母
            if (freq[cur] == 0) {
                cur = next;
            }
            // 若還有次大字母，則將一個次大字母加入 s 中
            else if (next >= 0) {
                s.push_back(('a' + next));
                --freq[next];
            }
            // 如果沒有次大字母了，無須再添加字母到 s 中，結束迴圈
            else {
                break;
            }
        }

        return s;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241217135005858.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241217135005858.png)

時間複雜度： $O(n)$ ，其中 $n$ 是 `s` 的長度。  
空間複雜度： $O(k)$ ，其中 $k$ 是 `s` 中不同字元的數量。  
