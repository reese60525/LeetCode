# <center> [3280. Convert Date to Binary](https://leetcode.com/problems/convert-date-to-binary/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501011147005.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501011147005.png)

給一個字串 `date` 代表一個日期，格式為 `YYYY-MM-DD`，請將其轉換為二進位表示。

## 解題思路

### 1. Bit Manipulation

將三個整數 `year`、`month`、`day` 從字串中取出，然後再透過位元運算將其轉換為二進位表示。

要算出整數 `n` 的二進制，可以用一個整數 `flag` 來和 `n` 做 `&` 運算，令 `flag` 為 `0...010..0` 的形式，1 的位置為 `n` 二進制中 1 的最高位位置，如果 `n & flag = 0` 則代表 $n$ 在 $flag$ 前導 1 的位置是 0，否則為 1，由此可得出 `n` 的二進制，而 `n` 最高位 1 的位置就會是 $\lfloor \log_2 n \rfloor$ 。

7 的二進制表示為 `0...0111`， $\lfloor \log_2 7 \rfloor = 2$ ，8 的二進制表示為 `0...01000`， $\lfloor \log_2 8 \rfloor = 3$，因此可以透過 $\lfloor \log_2 n \rfloor$ 來取得整數 `n` 的二進制表示中最高位 1 的位置。

實際操作流程：

假設有一個整數 `n` 其二進制為 $0...0110010010$ ，則 $flag = 1 << \lfloor log_2 n \rfloor = 0...0100000000$ ，`s = ""`

1. 將 `n` 和 `flag` 做 `&` 運算可得到 $0...0100000000 > 0$ ，因此該位置為 1，`s = "1"`，將 `flag` 右移一位。
2. 將 `n` 和 `flag` 做 `&` 運算可得到 $0...0010000000 > 0$ ，因此該位置為 1，`s = "11"`，將 `flag` 右移一位。
3. 將 `n` 和 `flag` 做 `&` 運算可得到 $0...0000000000 = 0$ ，因此該位置為 0，`s = "110"`，將 `flag` 右移一位。
4. 以此類推，直到 `flag` 為 0 時結束。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::string convertDateToBinary(std::string date) {
        // 將字串轉為整數
        int nums[3] = {(date[0] - '0') * 1000 + (date[1] - '0') * 100 + (date[2] - '0') * 10 + (date[3] - '0'),
                       (date[5] - '0') * 10 + (date[6] - '0'), (date[8] - '0') * 10 + (date[9] - '0')};

        // 將整數轉為二進制
        auto getBinary = [&](int num) -> std::string {
            // 取得最高位數
            int flag = 1 << (int)log2(num);
            std::string s = "";
            while (flag > 0) {
                // 若 num 在 flag 前導 1 的位置也是 1 則 c = '1' 反之 c = '0'
                char c = '0' + ((num & flag) > 0);
                s += c;
                flag >>= 1;
            }
            return s;
        };

        return getBinary(nums[0]) + '-' + getBinary(nums[1]) + '-' + getBinary(nums[2]);
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501011221249.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501011221249.png)

時間複雜度： $O(1)$ 。

空間複雜度： $O(1)$ 。

---

更簡單的方法就是直接將 `n` 和 1 做 $\bmod$ 運算來求二進制，如果 $n \bmod 2 = 0$ 則代表 `n` 最後一個 bit = 0，反之為 1，將其加入字串的最前面，然後 `num` 右移一位，直到 `num` 為 0 時結束。

`n mod 2 = n & 1` 。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::string convertDateToBinary(std::string date) {
        // 將字串轉為整數
        int nums[3] = {(date[0] - '0') * 1000 + (date[1] - '0') * 100 + (date[2] - '0') * 10 + (date[3] - '0'),
                       (date[5] - '0') * 10 + (date[6] - '0'), (date[8] - '0') * 10 + (date[9] - '0')};

        // 將整數轉為二進制
        auto getBinary = [&](int num) -> std::string {
            std::string s = "";
            while (num > 0) {
                s = ((num & 1) == 0) ? '0' + s : '1' + s;
                num >>= 1;
            }
            return s;
        };

        return getBinary(nums[0]) + '-' + getBinary(nums[1]) + '-' + getBinary(nums[2]);
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501011227586.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501011227586.png)

時間複雜度： $O(1)$ 。

空間複雜度： $O(1)$ 。
