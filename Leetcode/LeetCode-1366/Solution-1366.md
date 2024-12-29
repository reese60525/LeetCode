# <center> [1366. Rank Teams by Votes](https://leetcode.com/problems/rank-teams-by-votes/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412292154781.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412292154781.png)

給一個由大寫字母組成的字串陣列 `votes`，每個大寫字母代表一個隊伍的代號，`votes[i]` 代表第 `i` 個投票者所投的票，當一個隊伍的代號在 `votes[i]` 中越靠前，代表該隊伍在第 `i` 位投票者的的投票排名中越前面，而隊伍的總體排名則是根據每個隊伍在每個投票位置的排名來決定，如果在同樣的投票位置上，有兩個隊伍的排名相同，則繼續比較下一個投票位置，直到找到一個隊伍的排名比另一個隊伍的排名高為止，若全部投票位置的排名都一樣，則代號小的隊伍排名較高，回傳總體排名由高到低的隊伍代號字串。

- 每個 `votes[i]` 的長度都一樣
- `votes[i]` 中的每個 element 都是大寫字母，並且不重複
- 在 `votes[i]` 中出現的**所有字母**也都會全部出現在其他 `votes[j]` 中

e.g.  

votes = {"WXYZ", "XYZW"}

- 在 `votes[][0]` 中，W 出現了 1 次，X 出現了 1 次，Y 出現了 0 次，Z 出現了 0 次，因此目前排名是 W = X > Y = Z，繼續下一輪比較。
- 在 `votes[][1]` 中，X 出現了 1 次，Y 出現了 1 次，Z 出現了 0 次，W 出現了 0 次，在上一輪排名中 W = X 、 Y = Z，在這一輪 X > W 、 Y > Z，因此目前排名是 X > W > Y > Z。
- 確認完所有團體的排名後，排名為 X > W > Y > Z，return "XWYZ"。

## 解題思路

### 1. Hash Map and Sorting

遍歷 `votes` 中的每個投票，並使用一個 hash map `cnt` 來記錄每個隊伍在每個投票位置的得票數，然後自定義一個排序函數 `cmp`，將每個隊伍的得票數從高到低排序，最後將排序後的隊伍代號拼接成一個字串並回傳。  
以題目敘述的範例來說，隊伍 W 在各個投票位置的得票數分別為： {1, 0, 0, 1}，隊伍 X 在各個投票位置的得票數分別為： {1, 1, 0, 0} ... 以此類推，轉換為 `cnt` 就會是：

```text
cnt = {
    'W': [1, 0, 0, 1],
    'X': [1, 1, 0, 0],
    'Y': [0, 1, 1, 0],
    'Z': [0, 0, 1, 1]
}
```

進行排序後，會變成：

```text
cnt = {
    'X': [1, 1, 0, 0],
    'W': [1, 0, 0, 1],
    'Y': [0, 1, 1, 0],
    'Z': [0, 0, 1, 1]
}
```

也就是一種字典序的排列。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::string rankTeams(std::vector<std::string> &votes) {
        int n = votes.size(), m = votes[0].size();

        // cnt[][26] 紀錄這筆資料是哪個隊伍的
        std::vector<std::vector<int>> cnt(26, std::vector<int>(27));
        for (int i = 0; i < 26; ++i) {
            cnt[i][26] = i;
        }
        // 計算每個隊伍在每個投票位置的得票數
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int c = votes[j][i] - 'A';
                ++cnt[c][i];
            }
        }

        // 對 cnt 排序
        std::sort(cnt.begin(), cnt.end(), [&](auto &a, auto &b) {
            for (int i = 0; i < 26; ++i) {
                // 比較每個投票位置的得票數
                if (a[i] == b[i]) {
                    continue;
                }
                return a[i] > b[i];
            }
            // 如果得票數都相同，則比較隊伍的編號
            return a[26] < b[26];
        });

        // 將排序後的隊伍編號轉換為字串
        std::string res;
        for (int i = 0; i < m; ++i) {
            // cnt 最後一個 element 是隊伍的編號
            res += (cnt[i].back() + 'A');
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412292221680.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412292221680.png)

時間複雜度： $O(n \cdot m + m^2 \log m)$ ，其中 $n$ 是 `votes` 的長度， $m$ 是 `votes[0]` 的長度，計算每個隊伍在每個投票位置的得票數需要 $O(n \cdot m)$ 的時間，對 $m$ 個隊伍排序需要 $O(m \log m)$ ，由於每個隊伍又需要比對 $m$ 個投票位置，所以排序共需要 $O(m^2 \cdot \log m)$ 的時間。

空間複雜度： $O(m^2)$ 。
