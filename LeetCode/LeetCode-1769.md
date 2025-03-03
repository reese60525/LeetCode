# <center> [1769. Minimum Number of Operations to Move All Balls to Each Box](https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/description/) </center>

## 題目敘述

[![](https://i.imgur.com/hnNFHS8.png)](https://i.imgur.com/hnNFHS8.png)

給一個由 `'0'` 和 `'1'` 組成的字串 `boxes`，`boxes[i]` 代表該盒子裡面有或是沒有球，算出將所有球移動到每個盒子所需要的最小距離。

## 解題思路

### 1. Prefix Sum and Suffix Sum

假設當前在 `boxes[i]`，在左邊中範圍是 `[0, i-1]` 的球數  為 `left`，在右邊中範圍是 `[i, n-1]` 的球數為 `right`，如果此時向右移動一個 box，則左邊的球和當前 box 的距離會 + 1，右邊的球會減 - 1，利用這個特性可以預先算好在 $index = 0$ 時，左右兩邊的球數和每個球到 `boxes[0]` 的距離 `sum`，然後遍歷 `boxes`，每次向右移動一個 box 時左邊的球距離全 + 1，總共增加了 `right` 的距離，右邊的球距離全 - 1，總共減少了 `left` 的距離，將距離變化量累加到 `sum` 中就會是 `boxes[i]` 的答案。

此外如果 `boxes[i]` 為 1 則向右移動到 `boxes[i+1]` 時，左邊的球數會 + 1，右邊的球數會 - 1，所以 `left` 和 `right` 要相應的做加減。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> minOperations(std::string boxes) {
        // sum 為所有球到 index = i 的距離，一開始 i = 0
        // l 和 r 為 boxes 在 [0,i] 和 [i, n-1] 範圍中各有幾個球
        int sum = 0, l = 0, r = 0, n = boxes.size();
        for (int i = 0; i < n; ++i) {
            sum += (boxes[i] == '1') ? i : 0;
            r += (boxes[i] - '0');
        }

        std::vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            res[i] = sum;
            // 若當前 box 的有球，則計算下個 box 時左邊的球數會加一，右邊減一
            r -= (boxes[i] - '0');
            l += (boxes[i] - '0');
            // 往右移動一個 box，離左邊的球遠一步，離右邊的近一步
            sum -= r;
            sum += l;
        }

        return res;
    }
};
```

[![](https://i.imgur.com/IGbPpG7.png)](https://i.imgur.com/IGbPpG7.png)

#### 複雜度分析

令 $n$ 為 `boxes` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
