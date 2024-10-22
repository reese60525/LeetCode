/*
 * 題目: https://leetcode.com/problems/add-two-numbers/description/
 *
 * 題目解釋:
 * 給兩個儲存正整數的link list，各自代表一個整數的倒序，求將兩個link list相加後的倒序結果。
 * link list的長度不一定等長!
 * e.g. l1：1->5->3，l2：4->5->6，相加後為5->0->0->1。
 *
 * 思路:
 * 先將l1和l2持續相加，直到l1或l2的下個node為nullptr時停止。接著判斷l2是否比l1長，是的話就
 * 把l2剩下的部分加到l1的後面。最後依照k的值決定使否要進位，又分成兩種狀況：1.l1->next為nullptr時，
 * 直接將l1->next建立一個新的node，值為k，2.繼續將l1剩餘部分進行進位操作。
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
        ListNode *current = &dummy; // 指向虛擬頭節點的指針
        int carry = 0;              // 用於保存進位

        // 遍歷 l1 和 l2 直到兩者都為 nullptr，並處理進位
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry; // 初始值為進位

            if (l1 != nullptr) {
                sum += l1->val; // 加上 l1 當前節點的值
                l1 = l1->next;  // 移動到下一個節點
            }
            if (l2 != nullptr) {
                sum += l2->val; // 加上 l2 當前節點的值
                l2 = l2->next;  // 移動到下一個節點
            }

            carry = sum / 10;                       // 計算新的進位
            current->next = new ListNode(sum % 10); // 創建新節點存放相加的結果
            current = current->next;                // 移動指針到結果鏈表的下一個節點
        }

        return dummy.next; // 返回結果鏈表（跳過虛擬頭節點）
    }
};

int main() {

    return 0;
}