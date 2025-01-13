# <center> [301. Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501122006121.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501122006121.png)

給一個由小寫字母和左右括號組成的字串，可以移除任意的字元，找出所有**最長且不重複的**有效括號字串。

## 解題思路

### 1. DFS（Backtracking） and Branch Pruning

首先可以想到一個簡單的解法，就是用 DFS 窮舉所有可能的組合，並且在過程中記錄當前最長的有效括號字串。當然這樣的解法一定會 TLE，因此我們需要進行一些剪枝來優化，由於題目要求的是**最長且不重複**的有效括號字串，因此可以從這兩個方面來剪枝。

1. 預先計算出要變成**最長的**有效括號字串需要將左右括號移除的數量，這樣就不必在 DFS 過程中不斷更新最長有效括號字串的長度，並且當左右括號的移除數量超過預先計算的數量時，就可以直接剪枝。

2. 對於**不重複**的部分，以 {1, 2, 2, 3, 3, 2, 4} 為例，假設我們要選擇某些 element 形成一組不重複的 subset：

    ```text
    1 2 2 3 3 2 4
    1 2 - - - - 4
    1 - 2 - - - 4
    1 - - - - 2 4
    1 - - 3 - - 4
    1 - - - 3 - 4
    ```

   可以看到對於 subset = {1, 2, 4} 和 subset = {1, 3, 4} 來說，都會有重複的情況，這邊選擇保留第一次出現的 subset，並將其他重複的 subset 剪枝。那麼該如何判斷是否可以保留 subset 呢？這邊的前提是先執行**保留當前 element** 的 DFS 再執行**不保留當前 element** 的 DFS。

    - 當處於「丟棄」某個 element 的回溯路徑時，又嘗試選擇這個 element（或後面其他與之相同的 element），會導致重複結果。
        - 例如，1 - 2 - - - 4 和 1 - - - - 2 4 都是從 1 出發，但在第二個 element 時選擇拋棄了 2，後續又選擇不同的 2 組成的結果，實際上會和 1 2 - - - - 4 重複。  
        - 更深入地討論造成這樣結果的原因，是由於一定會先選擇第一個 2（上面的前提保證會先執行**保留當前 element 的 DFS**），而 1 2 \* \* \* \* \* 這些組合（\* 代表選或不選任意 element）也都比不選擇第一個 2（也就是 1 \* \* \* \* \* \*）還要更早被遍歷到，所以後續選擇了已經被拋棄的 element 就會導致重複。

    - 如果在丟棄過程中添加了其他新 element，則這段路徑不會與之前的結果重複
        - 例如，1 2 - 3 - - 4 和 1 - - 3 - 2 4 並不重複，因為後者在丟棄 2 後添加了新的 element （3），但要注意的是，1 2 - 3 - - 4 和 1 - 2 3 - - 4 仍然是重複的，因為後者選擇被丟棄的 2 早於添加新的 3，這兩個結果實際上是一樣的。

    - 綜合以上兩點可以得出結論，在當前已經選擇的 subset 中，從最後一個被選擇的 element 開始，到當前的 element 之間，這些被拋棄的 elements 不可以再被選擇，否則會導致重複。
        - 例如有個 set = {1, 1, 2, 2, 3, 3, 3, 5, 5, 5, 6, 6}，假如當前的 subset = {1, -, -, -, -, -, -, -, 5, ?, ?, ?}（問號表示尚未遍歷到），從最後一個被選擇的 element（1）開始，到當前的 element（5）之間，這些被拋棄的 elements（1、2、3、5） 都不可以再被選擇，否則會導致重複。  
        - 再舉一個例子，set = {1, 1, 2, 2, 3, 3, 1, 5, 5, 5, 6, 6}，當前的 subset = {1, 1, -, -, 3, -, 1, 5, -, ?, ?, ?}，這樣的組合就不會有重複的情況，因為每個被拋棄的 element 都沒有再次被選擇。如果是 {1, 1, -, 2, 3, -, 1, 5, -, ?, ?, ?} 的話，在第四個 element 選擇了已經被拋棄的 2，那麼會有 {1, 1, 2, -, 3, -, 1, 5, -, \*, \*, \*} 這樣的組合會先被遍歷到，導致重複。

    最後以一個簡單的例子完整展示用 DFS 窮舉 {2, 2, 3 ,3} 所有**不重複**的 subset：

    ```text
    2 2 3 3
    2 2 3 -
    2 2 - 3 重複，從 {2 2} 開始丟棄了 3，後面又選擇了 3，導致重複
    2 2 - -
    2 - 3 3
    2 - 3 -
    2 - - 3 重複，從 {2} 開始丟棄了 3，後面又選擇了 3，導致重複
    2 - - -
    - 2 3 3 重複，從 {} 開始丟棄了 2，後面又選擇了 2，導致重複
    - 2 3 - 重複，從 {} 開始丟棄了 2，後面又選擇了 2，導致重複
    - 2 - 3 重複，從 {} 開始丟棄了 2，後面又選擇了 3，導致重複
    - 2 - - 重複，從 {} 開始丟棄了 2，後面又選擇了 3，導致重複
    - - 3 3
    - - 3 -
    - - - 3 重複，從 {- -} 開始丟棄了 3，後面又選擇了 3，導致重複
    - - - -
    ```

    一般而言會用一個 `std::unordered_map` 來紀錄從最後一個 element 到現在這之間已經被丟棄的 elements，如果當前 element 被選擇了，則要將 `map` 重置為空傳入下個 `DFS`，如下所示：

    ```cpp {.line-numbers}
    dfs(const std::vector<int> &set,std::vector<int> &subset,int index,std::unordered_map<int, int> &skipped){
        // 從 subset 最後一個被選擇的 element 到當前的 element（set[index]） 之間
        // set[index] 被丟棄的次數為 0，可以選擇該 element
        if(skipped[set[index]] == 0){
            std:::unordered_map<int, int> new_skipped; // 當前選擇了一個新的 element，創建空的 skipped
            subset.push_back(set[index]);
            dfs(set, subset, index + 1, new_skipped); // 傳入空的 skipped
            subset.pop_back();
        }
        // 丟棄當前 element，並將其加入 skipped
        ++skipped[set[index]];
        dfs(set, subset, index + 1, skipped);
        // 回朔到上一層時，將其從 skipped 中移除
        --skipped[set[index]];
    }
    ```

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<std::string> removeInvalidParentheses(std::string s) {
        // 計算需要刪除的左右括號數量，確保最長的合法括號字串
        int l_to_delete = 0, r_to_delete = 0, n = s.size();
        for (char &c : s) {
            if (c == '(') { // 遇到左括號，增加未匹配的左括號數量
                ++l_to_delete;
            }
            else if (c == ')') {
                if (l_to_delete > 0) { // 若有左括號可以匹配，則匹配左括號
                    --l_to_delete;
                }
                else { // 沒有可匹配的左括號，右括號需要移除的數量 +1
                    ++r_to_delete;
                }
            }
        }

        std::vector<std::string> res;
        auto dfs = [&](auto &&dfs, int l, int r, int balance, int index, std::string &cur,
                       std::unordered_map<char, int> &skipped) {
            if (balance < 0) { // 左括號數量小於右括號數量，無效括號字串
                return;
            }
            if (index == n) { // 已遍歷完字串，檢查是否為最長的合法括號字串
                if (balance == 0 && l == 0 && r == 0) {
                    res.emplace_back(cur);
                }
                return;
            }

            if (s[index] == '(') {
                // 若左括號沒有被丟棄過才可以選擇，避免重複的字串組合
                if (skipped['('] == 0) {
                    std::unordered_map<char, int> new_skipped; // 當前選擇了一個新的 element，創建空的 skipped
                    cur += '(';
                    dfs(dfs, l, r, balance + 1, index + 1, cur, new_skipped); // 傳入空的 skipped
                    cur.pop_back();
                }
                // 檢查是否還有左括號可以刪除，若有則刪除左括號，並且 skipped +1 表示左括號被丟棄的次數 +1
                if (l > 0) {
                    ++skipped['('];
                    dfs(dfs, l - 1, r, balance, index + 1, cur, skipped);
                    --skipped['('];
                }
            }
            else if (s[index] == ')') {
                // 若右括號沒有被丟棄過才可以選擇，避免重複的字串組合
                if (skipped[')'] == 0) {
                    std::unordered_map<char, int> new_skipped; // 當前選擇了一個新的 element，創建空的 skipped
                    cur += ')';
                    dfs(dfs, l, r, balance - 1, index + 1, cur, new_skipped); // 傳入空的 skipped
                    cur.pop_back();
                }
                // 檢查是否還有左括號可以刪除，若有則刪除左括號，並且 skipped +1 表示右括號被丟棄的次數 +1
                if (r > 0) {
                    ++skipped[')'];
                    dfs(dfs, l, r - 1, balance, index + 1, cur, skipped);
                    --skipped[')'];
                }
            }
            else {                                         // 若為其他字元，直接加入字串
                std::unordered_map<char, int> new_skipped; // 當前選擇了一個新的 element，創建空的 skipped
                cur += s[index];
                dfs(dfs, l, r, balance, index + 1, cur, new_skipped); // 傳入空的 skipped
                cur.pop_back();
            }
        };

        std::string cur;
        std::unordered_map<char, int> skipped;
        dfs(dfs, l_to_delete, r_to_delete, 0, 0, cur, skipped);

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501130049686.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501130049686.png)

時間複雜度： $O(2^n)$ ，其中 $n$ 為字串 `s` 的長度，考慮到每個字元都有選擇和不選擇兩種情況，總共有 $2^n$ 種組合。

空間複雜度： $O(n)$ ，遞迴深度最多為 $n$ ，需要 $O(n)$ 的空間來儲存遞迴時的狀態。

---

由於在這道題目中只需要考慮 `(` 和 `)` 兩種字元，因此可以將 `std::unordered_map` 改為整數，以整數的最低位元用來確認是否可以選擇左括號，次低位元用來確認是否可以選擇右括號。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<std::string> removeInvalidParentheses(std::string s) {
        // 計算需要刪除的左右括號數量，確保最長的合法括號字串
        int l_to_delete = 0, r_to_delete = 0, n = s.size();
        for (char &c : s) {
            if (c == '(') { // 遇到左括號，增加未匹配的左括號數量
                ++l_to_delete;
            }
            else if (c == ')') {
                if (l_to_delete > 0) { // 若有左括號可以匹配，則匹配左括號
                    --l_to_delete;
                }
                else { // 沒有可匹配的左括號，右括號需要移除的數量 +1
                    ++r_to_delete;
                }
            }
        }

        std::vector<std::string> res;
        auto dfs = [&](auto &&dfs, int l, int r, int balance, int skipped, int index, std::string &cur) {
            if (balance < 0) { // 左括號數量小於右括號數量，無效括號字串
                return;
            }
            if (index == n) { // 已遍歷完字串，檢查是否為最長的合法括號字串
                if (balance == 0 && l == 0 && r == 0) {
                    res.emplace_back(cur);
                }
                return;
            }

            if (s[index] == '(') {
                // skipped 最低位 bit 為 0 表示前面沒有丟棄左括號，因此可以選擇當前左括號
                if (!(skipped & 0b1)) {
                    cur += '(';
                    dfs(dfs, l, r, balance + 1, 0, index + 1, cur); // 將 skipped 重置為 0
                    cur.pop_back();
                }
                // 檢查是否還有左括號可以刪除，若有則刪除左括號，並且 skipped 最低位設為 1 表示 "不選擇左括號"
                if (l > 0) {
                    dfs(dfs, l - 1, r, balance, skipped | 0b1, index + 1, cur);
                }
            }
            else if (s[index] == ')') {
                // skipped 次低位 bit 為 0 表示前面沒有丟棄右括號，因此可以選擇當前右括號
                if (!(skipped & 0b10)) {
                    cur += ')';
                    dfs(dfs, l, r, balance - 1, 0, index + 1, cur); // 將 skipped 重置為 0
                    cur.pop_back();
                }
                // 檢查是否還有右括號可以刪除，若有則刪除右括號，並且 skipped 次低位設為 1 表示 "不選擇右括號"
                if (r > 0) {
                    dfs(dfs, l, r - 1, balance, skipped | 0b10, index + 1, cur);
                }
            }
            else { // 若為其他字元，直接加入字串
                cur += s[index];
                dfs(dfs, l, r, balance, 0, index + 1, cur);
                cur.pop_back();
            }
        };

        std::string cur;
        dfs(dfs, l_to_delete, r_to_delete, 0, 0, 0, cur);

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501130702514.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501130702514.png)

時間複雜度： $O(2^n)$ ，其中 $n$ 為字串 `s` 的長度，考慮到每個字元都有選擇和不選擇兩種情況，總共有 $2^n$ 種組合。

空間複雜度： $O(n)$ ，遞迴深度最多為 $n$ ，需要 $O(n)$ 的空間來儲存遞迴時的狀態。

### 2. BFS

要找**最長**的合法括號字串，可以當作找**刪除最少字元**的合法括號字串，因此可以使用 BFS 來解題。

在每一層 BFS 中，遍歷當前層的合法括號字串，刪減該字串某個字元，並檢查是否為合法括號字串，若是合法括號字串則加入到 `res`，並在結束該層 BFS 後返回 `res`，此時 `res` 中儲存的括號字串即為最長（刪除最少字元）的合法括號字串，若該層沒有合法括號字串則繼續下一層 BFS。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<std::string> removeInvalidParentheses(std::string s) {
        // 若字串本身為合法括號字串，則直接返回
        if (isValid(s)) {
            return {s};
        }

        std::queue<std::string> q;
        q.push(s);

        while (!q.empty()) {
            // non_repeat_res 用來儲存當前層的合法括號字串，children 用來儲存下一層的合法括號字串
            // 必須要用 std::unordered_set 來儲存，不然大量的重複字串會導致 MLE
            std::unordered_set<std::string> non_repeat_res, children;
            int n = q.size();
            // 遍歷當前層的括號字串
            for (int i = 0; i < n; ++i) {
                std::string cur = q.front();
                q.pop();

                // 刪減該字串某個字元，並檢查是否為合法括號字串，若是則加入 non_repeat_res 中
                for (int j = 0; j < cur.size(); ++j) {
                    // 剪枝，若當前字元與前一個字元相同則跳過
                    if (j > 0 && cur[j] == cur[j - 1]) {
                        continue;
                    }
                    // 跳過非括號字元
                    if (cur[j] != '(' && cur[j] != ')') {
                        continue;
                    }

                    std::string tmp = cur;
                    tmp.erase(tmp.begin() + j);
                    !isValid(tmp) ? children.insert(tmp) : non_repeat_res.insert(tmp);
                }
            }

            // 若當前層的合法括號字串數量 > 0，則返回當前層的合法括號字串
            // 這樣所得到的括號字串是刪除最少字元數的合法括號字串
            if (non_repeat_res.size() > 0) {
                return {non_repeat_res.begin(), non_repeat_res.end()};
            }
            else {
                for (auto &child : children) {
                    q.push(child);
                }
            }
        }

        return {""};
    }

    // 檢查括號字串是否合法
    bool isValid(const std::string &s) {
        int balance = 0;

        for (const char &c : s) {
            balance += c == '(';
            balance -= c == ')';
            if (balance < 0) {
                return false;
            }
        }

        return balance == 0;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501130912600.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501130912600.png)

時間複雜度： $O(n \cdot 2^n)$  
在 BFS 中，我們逐層處理所有狀態。在最壞情況下，我們需要處理所有的層級。因此，我們可以逐層分析時間複雜度，並將其相加以獲得最終的時間複雜度。

在第一層，只有一個字串，即輸入字串 $s$。假設其長度為 $n$，檢查它是否合法需要 $O(n)$ 的時間。  
在第二層，從第一層中刪除一個 `(` 或 `)`，因此有 $C(n, n-1)$ 個新字串。這些字串的長度為 $n-1$ ，對於每個字串，我們需要檢查其是否合法。於是，這一層的總時間複雜度為： $O((n-1) \times C(n, n-1))$ 。  
在第三層，時間複雜度為： $O((n-2) \times C(n, n-2))$ 。  
以此類推 ... 最後可得到以下的時間複雜度：

$T(n) = n \times C(n, n) + (n-1) \times C(n, n-1) + (n-2) \times C(n, n-2) + \cdots + 1 \times C(n, 1) = O(n \cdot 2^n)$

空間複雜度： $O(n \cdot 2^n)$ ，在 BFS 中，我們需要儲存每一層的括號字串。
