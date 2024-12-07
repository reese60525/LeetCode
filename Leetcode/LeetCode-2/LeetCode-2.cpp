#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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

int main() {

    return 0;
}