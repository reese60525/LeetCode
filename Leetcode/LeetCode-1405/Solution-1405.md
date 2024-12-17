# <center> [LeetCode - 1405. Longest Happy String](https://leetcode.com/problems/longest-happy-string/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241217170008995.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241217170008995.png)

給三個 integer `a`、`b`、`c`，分別代表三個字母 'a'、'b'、'c' 的數量，請找出由這些 'a'、'b'、'c' 所組成的最長 happy string。  

happy string 的定義為：

- 字串中不能有連續三個或以上的相同相鄰字母，e.g. "aaa"、"aaaa" ...  
- 字串中只能有 'a'、'b'、'c' 這三種字母

**最長 happy string 可能不只有一種!回傳任意一種就好**

e.g.

1. `a` = 1，`b` = 1，`c` = 7  
    最長的 happy string 為 "ccaccbcc" 或是 "ccbccacc"  

2. `a` = 7，`b` = 1，`c` = 0  
    最長的 happy string 為，"aabaa" ，

## 解題思路

### 1. Greedy and Priority Queue

每次都從三個字母中選擇數量最多的字母，如果該字母沒有連續出現超過兩次，就將該字母加入 `res` 中，並將該字母的數量減一，反之則選擇數量第二多的字母加入 `res` 中，並將該字母的數量減一，如果沒有第二個字母可以選，則跳出迴圈 return  `res`。

#### 程式碼

```cpp {.line-numbers}
/*
 *  File        : LeetCode-1405.cpp
 *  Author      : Reese
 *  Created On  : 2024-12-17 15:13
 *  Description : https://leetcode.com/problems/longest-happy-string/
 */

class Solution {
  public:
    std::string longestDiverseString(int a, int b, int c) {
        // 若出現次數為 0 則不用加入 pq
        std::priority_queue<std::pair<int, char>> pq;
        a > 0 ? pq.push({a, 'a'}) : void();
        b > 0 ? pq.push({b, 'b'}) : void();
        c > 0 ? pq.push({c, 'c'}) : void();

        std::string res;
        res.reserve(a + b + c);
        while (!pq.empty()) {
            // 取出出現次數最多的字元
            auto [cnt, ch] = pq.top();
            pq.pop();

            // 若前兩個字元與當前字元相同，則加入出現次數第二多的字元
            if (res.size() > 1 && res[res.size() - 1] == ch && res[res.size() - 2] == ch) {
                // 若沒有第二多的字元，則離開迴圈
                if (pq.empty()) {
                    break;
                }

                auto [cnt2, ch2] = pq.top();
                pq.pop();
                res.push_back(ch2);
                // 如果出現次數變成 0 就不用放回 pq
                if (--cnt2 > 0) {
                    pq.push({cnt2, ch2});
                }
            }
            else {
                res.push_back(ch);
                --cnt;
            }
            // 如果出現次數變成 0 就不用放回 pq
            if (cnt > 0) {
                pq.push({cnt, ch});
            }
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241217174241472.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241217174241472.png)

時間複雜度: $O(a+b+c)$ ，其中 $a$ 、 $b$ 、 $c$ 分別為三個字母的數量。  
空間複雜度: $O(1)$ ，回傳值不計入空間使用。  
