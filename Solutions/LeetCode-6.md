# <center> [6. Zigzag Conversion](https://leetcode.com/problems/zigzag-conversion/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226140426327.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226140426327.png)

給一個字串 `s` 和正整數 `numRows`，令 `s` 以高度為 `numRows` 的鋸齒狀呈現，回傳以橫列由上而下讀所得到的字串。

e.g.

$s = "PAYPALISHIRING"$ ， $numRows = 3$

- 先將其以高度為 3 的鋸齒狀呈現，如下所示。

    ```text
    P       A       H       N
      A   P   L   S   I   I   G
        Y       I       R
    ```

- 接著再以由上而下橫行來看，會得到 `["PAHN", "APLSIIG", "YIR"]`，將其合併後得到 `"PAHNAPLSIIGYIR"` 並回傳。

## 解題思路

### 1. Simulation

直接模擬鋸齒狀字串的建構過程，創建一個大小為 `numRows` 的陣列 `rows`，用來儲存每一列的字母，從 $index = 0$ 遍歷 `s` 中的每個字元，令 `k` 為當前字元在 `rows` 中的 index，若 $k = 0$ 或 $k = numRows - 1$ ，表示已經到達鋸齒狀的邊界，此時要轉變方向，假如原本 `k` 是遞增的，則變成遞減，反之亦然。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::string convert(std::string s, int numRows) {
        // 能直接 return s 的情況
        if (numRows == 1 || s.length() <= numRows) {
            return s;
        }

        std::vector<std::string> rows(numRows);
        int idx = 0, dir = -1; // 紀錄 rows 的 index 和當前的行徑方向（往上或往下）
        for (char &c : s) {
            rows[idx] += c;

            // 到達鋸齒狀邊界要轉方向
            if (idx == 0 || idx == numRows - 1) {
                dir *= -1;
            }
            idx += dir;
        }

        std::string res;
        for (std::string &s : rows) {
            res += s;
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226143427916.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226143427916.png)

#### 複雜度分析

令 $n$ 為字串 `s` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(n)$

### 2. Grouped Loop

觀察以下字串：  

```text
a                   a                   a                   a
  a               a   a               a   a               a   a
    a           a       a           a       a           a       a
      a       a           a       a           a       a           a
        a   a               a   a               a   a               a
          a                   a                   a                   a
```

該鋸齒狀的字串循環週期為 $t = 2 \cdot numRows - 2$ ，例如 `s[3]` 經過一個週期後會出現在 `s[13]`。除了第一列和最後一列以外，其他列每一次循環週期都會出現兩個 element，令 `i` 表示現在是第幾列（從 0 開始），`j` 表示現在是第 `j` 次週期，則當前週期當前列第一個 element 的 $index = j \cdot t + i$ ，當前週期當前列第二個 element 的 $index = (j + 1) \cdot t - i$ ，換句話說，第 `i` 個週期的起點是在 $index = j \cdot t$ ，往下走 `i` 步會得到該週期第 `i` 列的第一個 element，而第二個 element 可以看做下一個週期的起點 $index = (j + 1) \cdot t$ 往回走 `i` 步。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::string convert(std::string s, int numRows) {
        // 能直接 return s 的情況
        if (numRows == 1 || s.length() <= numRows) {
            return s;
        }

        int t = numRows * 2 - 2; // 循環週期
        std::string res;
        res.reserve(s.length());
        for (size_t i = 0; i < numRows; ++i) {
            for (size_t j = 0; j + i < s.length(); j += t) {
                // 當前週期起點往下走 i 步就會得到第 i 列的第一個 element
                res += s[j + i];
                // 第一列和最後一列的一個週期一列只有一個 element，所以不能再加右邊的 element
                // 下個週期的起點往回走 i 步就會得到第 i 列的第二個 element
                if (i != 0 && i != numRows - 1 && j + t - i < s.length()) {
                    res += s[(j + t) - i];
                }
            }
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226181354152.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241226181354152.png)

#### 複雜度分析

令 $n$ 為字串 `s` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
