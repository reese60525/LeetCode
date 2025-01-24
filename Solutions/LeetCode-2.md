# <center> [2. Add Two Numbers](https://leetcode.com/problems/add-two-numbers/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210160801270.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210160801270.png)

給兩個儲存正整數的 linked lists，各自代表一個整數的倒序，求將兩個link list相加後的倒序結果。

**link list的長度不一定等長!**

e.g.

$l1 = [1, 5, 3]$ ， $l2 = [4, 5, 6]$ ， $carry = 0$

- $1 + 4 + 0 = 5$ ， $carry = 0$ ， $res = [5]$ 。

- $5 + 5 + 0 = 10$ ， $carry = 1$ ， $res = [5, 0]$ 。

- $3 + 6 + 1 = 10$ ， $carry = 1$ ， $res = [5, 0, 0]$ 。

- 放入最後的 `carry`， $res = [5, 0, 0, 1]$ 。

## 解題思路

### Linked List

創建一個新的 linked list 來存放 `l1` 和 `l2` 相加的結果，`dummy` 是一個 linked list 的虛擬頭節點，其指向一個 link list 的 `head`，也就是說 `dummy->next` 才是真正的 `head`。

遍歷 `l1` 和 `l2` 將其當前的值和 `carry` 相加，將 $carry \mod 10$ 存入新的 linked list node 中，直到 `l1` 和 `l2` 遍歷完，如果 $carry \neq 0$ ，則將 `carry` 加入新的 link list 中。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode dummy(0);          // 創建一個虛擬頭節點
        ListNode *current = &dummy; // 指向虛擬頭節點的指標
        int carry = 0;              // 用於保存進位

        // 遍歷l1和l2直到兩者都為nullptr，並處理進位
        while (l1 != nullptr || l2 != nullptr || carry != 0) {

            if (l1 != nullptr) {
                carry += l1->val; // 加上l1當前節點的值
                l1 = l1->next;    // 移動到下一個節點
            }
            if (l2 != nullptr) {
                carry += l2->val; // 加上l2當前節點的值
                l2 = l2->next;    // 移動到下一個節點
            }

            // 創建新節點存放相加的結果
            current = current->next = new ListNode(carry % 10);
            carry = carry > 9 ? 1 : 0; // 計算新的進位
        }

        return dummy.next; // 返回結果鏈表（跳過虛擬頭節點）
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241207201049415.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241207201049415.png)

#### 複雜度分析

令 $m$ 和 $n$ 分別是 `l1` 和 `l2` 的長度。

- 時間複雜度： $O(\max (m, n))$

- 空間複雜度： $O(1)$
