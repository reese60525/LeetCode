/*
 * 題目： https://leetcode.com/problems/swap-nodes-in-pairs/description/
 *
 * 題目解釋：
 * 給一個整數linked list，從head node開始，將相鄰的node的值交換。
 * e.g. {} -> {}， {1} -> {1}， {1, 2} -> {2, 1}， {1, 2, 3} -> {2, 1, 3}
 *
 * 思路：
 * 要交換的兩個node不能是nullptr才能交換。
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
    ListNode *swapPairs(ListNode *head) {
        ListNode *cur = head;

        while (cur != nullptr && cur->next != nullptr) {
            int temp = cur->val;
            cur->val = cur->next->val;
            cur->next->val = temp;
            cur = cur->next->next;
        }

        return head;
    }
};

int main() {

    return 0;
}