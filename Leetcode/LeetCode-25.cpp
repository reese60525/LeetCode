/*
 * 題目： https://leetcode.com/problems/reverse-nodes-in-k-group/description/
 *
 * 題目解釋：
 * 給一個linked list和整數k，將linked list的node每k個分成一組，將每組的連接方向反轉，
 * 不足k個的那組不用反轉，將這些反轉後的linked list串起來並回傳head。
 * e.g. linked list = {1, 2, 3, 4, 5, 6, 7, 8}，k = 3，分組反轉後會變成
 * {{3, 2, 1}, {6, 5, 4}, {7, 8}}，串起來得到新的linked list = {3, 2, 1, 6, 5, 4, 7, 8}
 *
 * 思路：
 * 判斷剩餘node有沒有>=k個，不夠的話直接回傳head，夠的話就開始reverse，將每個node都指向前一個node，
 * 像是1->2->3會變成3->2->1->nullptr，而一開始的head(1)要指向下一組反轉後的head，因此可以用下一組
 * 的head去遞迴這個reverseKGroup function，將反轉後的head回傳，不斷重複遞迴即可得到答案。
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
    ListNode *reverseKGroup(ListNode *head, int k) {
        ListNode *cur = head;

        // 檢查剩下的node夠不夠reverse
        for (int i = 0; i < k; ++i) {
            if (cur == nullptr) {
                return head;
            }
            cur = cur->next;
        }

        // 將所有node指向前一個node，head會先指向nullptr
        cur = head;
        ListNode *pre = nullptr;
        ListNode *next = nullptr;
        for (int i = 0; i < k; ++i) {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }

        // 將最後一個node(head)指向下一個group反轉後的head
        head->next = reverseKGroup(cur, k);
        // 返回反轉後的head
        return pre;
    }
};

int main() {

    return 0;
}