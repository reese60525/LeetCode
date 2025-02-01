# <center> [LeetCode - 1792. Maximum Average Pass Ratio](https://leetcode.com/problems/maximum-average-pass-ratio/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241215104556830.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241215104556830.png)

給一個二維整數陣列 `classes`， $classes[i] = [pass_i, total_i]$ ，代表第 `i` 個班級有 `pass_i` 個人通過考試，該班級總共有 `total_i` 個人 。以及一個整數 `extraStudents`，代表你可以額外分配 `extraStudents` 個學生到任何班級，這些學生一定會通過考試，將這些學生分配到班級後，將每個班級的通過率加總並平均後的最大值是多少？

e.g.

$classes = [[1, 2], [3, 5], [2, 2]]$ ， $extraStudents = 2$

將兩個學生都分配到第一個班級，通過率為 $\frac{1+2}{2+2} = \frac{3}{4} = 0.75$

接著將所有班級的通過率加總後除以班級數，得到平均通過率為 $\frac{0.75 + 0.6 + 1}{3} = 0.78333$

該平均通過率為任意分配學生的方式中的最大值。

## 解題思路

### 1. Greedy and Priority Queue

這題的關鍵在於如何保證分配學生後的通過率最大，假設某個班級的 `pass` 和 `total` 分別為 `p` 和 `t`，則該班級的通過率為 $\frac{p}{t}$ 。當分配一個學生到該班級，則通過率為 $\frac{p+1}{t+1}$ ，我們可以發現，分配學生後的通過率增加量為 $\frac{p+1}{t+1} - \frac{p}{t} = \frac{t(p+1) - p(t+1)}{t(t+1)} = \frac{t-p}{t(t+1)}$ ，因此可以創建一個 max heap 的 priority queue 存放 `classes` 以**通過率增加量**來做排序，每次從 priority queue 中取出通過率增加量**最大**的班級，將學生分配到該班級，直到所有學生都被分配完為止，這樣就能保證分配學生後的通過率是最大的。

而兩個班級的通過率增加量的比較公式為： $\frac{t_1-p_1}{t_1(t_1+1)} > \frac{t_2-p_2}{t_2(t_2+1)}$ ，可以將兩邊同乘 $t_1(t_1+1)$ 和 $t_2(t_2+1)$ ，得到 $(t_1-p_1)t_2(t_2+1) > (t_2-p_2)t_1(t_1+1)$ ，通過這樣的比較方式可以避免除法浮點數的誤差。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    typedef std::pair<int, int> PII;

    double maxAverageRatio(std::vector<std::vector<int>> &classes, int extraStudents) {
        // priority queue 的比較函數，要將分子或是分母轉成 long long 型態，避免乘法溢位
        auto cmp = [](PII &p1, PII &p2) {
            return (p1.second - p1.first) * (static_cast<long long>(p2.second) * (p2.second + 1)) <
                   (p2.second - p2.first) * (static_cast<long long>(p1.second) * (p1.second + 1));
        };

        // 創建 priority queue，並將 classes 放入
        std::priority_queue<PII, std::vector<PII>, decltype(cmp)> pq;
        for (auto &c : classes) {
            pq.push({c[0], c[1]});
        }

        // 將 extraStudents 一一加入到各個 class 中
        while (extraStudents--) {
            auto [pass, total] = pq.top();
            pq.pop();
            pq.push({pass + 1, total + 1});
        }

        // 計算通過率平均值
        double res = 0;
        while (!pq.empty()) {
            auto [pass, total] = pq.top();
            pq.pop();
            res += static_cast<double>(pass) / total;
        }

        return res / classes.size();
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241215112102327.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241215112102327.png)

#### 複雜度分析

令 $n$ 為 `classes` 的長度， $k$ 為 `extraStudents` 的值。

- 時間複雜度: $O((n+k) \cdot \log n)$

- 空間複雜度: $O(n)$

---
對於這個方式，每次操作 priority queue 時都必須將每個 `class` 的通過率增加量**全部重新計算一次**，導致效能低下，因此可以改變 priority queue 的資料結構，從原本的 `[pass, total]` 改為 `[ratio, (pass, total)]` ，其中 `ratio` 為通過率增加量，這樣就可以在操作 priority queue 之後的維護可以不用每個 element 都呼叫 `cmp` 來比較，直接用 `ratio` 來比較即可，減少許多運算。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    double maxAverageRatio(std::vector<std::vector<int>> &classes, int extraStudents) {
        // 計算通過率增加量的函數
        auto diff = [](int pass, int total) {
            return static_cast<double>((pass + 1)) / (total + 1) - static_cast<double>(pass) / total;
        };

        double res = 0;
        std::priority_queue<std::pair<double, std::array<int, 2>>> pq;
        for (size_t i = 0; i < classes.size(); ++i) {
            // 將基礎通過率累加到 res 中，這一步驟可以省略後面要遍歷 pq 算出 res 的步驟
            res += static_cast<double>(classes[i][0]) / classes[i][1];
            // 將各班級的通過率增加量和 class 放入 pq 中
            pq.push({
                diff(classes[i][0], classes[i][1]), {classes[i][0], classes[i][1]}
            });
        }

        // 將學生一一分配給通過率增加量最大的班級
        while (extraStudents--) {
            auto [ratio, cls] = pq.top();
            pq.pop();
            // 累加通過率增加量
            res += ratio;
            // 更新 pq
            pq.push({
                diff(cls[0] + 1, cls[1] + 1), {cls[0] + 1, cls[1] + 1}
            });
        }

        return res / classes.size();
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241215115130556.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241215115130556.png)

#### 複雜度分析

令 $n$ 為 `classes` 的長度， $k$ 為 `extraStudents`

- 時間複雜度: $O((n+k) \cdot \log n)$

- 空間複雜度: $O(n)$
