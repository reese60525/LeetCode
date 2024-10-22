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
        int k = 0;           // k用來表示進位
        ListNode *head = l1; // 紀錄l1的起始位置

        while (true) {
            int sum = l1->val + l2->val + k; // 計算兩個node的值和進位的總和
            l1->val = sum % 10;              // 計算進位後的值
            k = sum / 10;                    // 計算進位

            if (!l1->next || !l2->next) { /// 當l1或l2的下一個node為nullptr時就跳出迴圈
                break;
            }

            l1 = l1->next;
            l2 = l2->next;
        }

        if (l2->next) { // 當l2的長度大於l1時，將l2的剩餘部分加到l1的後面
            l1->next = l2->next;
        }

        while (k) {          // 當k不為0時，l1要繼續計算進位
            if (!l1->next) { // 當l1的下一個node為nullptr時，建立新的node，值為k
                l1->next = new ListNode(k);
                break;
            }

            // 若l1的下一個node不為nullptr，繼續計算進位
            l1 = l1->next; // 當前l1是已經計算過的，所以要切換至下個node
            int sum = l1->val + k;
            l1->val = sum % 10;
            k = sum / 10;
        }

        return head;
    }
};

int main() {

    return 0;
}