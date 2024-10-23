/*
 * 題目：https://leetcode.com/problems/add-two-numbers/description/
 *
 * 題目解釋：
 * 給兩個儲存正整數的link list，各自代表一個整數的倒序，求將兩個link list相加後的倒序結果。
 * link list的長度不一定等長!
 * e.g. l1：1->5->3，l2：4->5->6，相加後為5->0->0->1。
 *
 * 思路：
 * 創建一個新的link list來存放l1和l2相加的結果，dummy是一個link list的虛擬頭節點，其指向
 * 一個link list的head，也就是說dummy->next才是真正的head。遍歷l1和l2將其當前的值和carry
 * 相加，將得到的值%10存入新的link list中，直到l1和l2遍歷完，若是carry不為0，則將carry加入
 * 新的link list中。
 */
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
            int sum = carry; // 初始值為進位

            if (l1 != nullptr) {
                sum += l1->val; // 加上l1當前節點的值
                l1 = l1->next;  // 移動到下一個節點
            }
            if (l2 != nullptr) {
                sum += l2->val; // 加上l2當前節點的值
                l2 = l2->next;  // 移動到下一個節點
            }

            carry = sum / 10;                       // 計算新的進位
            current->next = new ListNode(sum % 10); // 創建新節點存放相加的結果
            current = current->next;
        }

        return dummy.next; // 返回結果鏈表（跳過虛擬頭節點）
    }
};

int main() {

    return 0;
}