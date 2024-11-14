/*
 * 題目： https://leetcode.com/problems/merge-two-sorted-lists/description/
 *
 * 題目解釋：
 * 給兩個sorted linked list，將兩個list合併成一個sorted linked list。
 *
 * 思路：
 * 對list1創建一個dummy，dummy -> list1，假設list1 = {1, 3, 5}、list2 = {2, 4, 6}、
 * dummy = {0, 1, 3, 5}，要合併成一個sorted linked list，首先判斷list2當前node的value(2)
 * 是否小於dummy->next的value(1)，如果是的話則將其插入，不斷重複這個動作直到dummy->next或
 * list2為nullptr。之後判斷list2的點是否全部插入到list1，如果還有剩餘的node則將其插入到list1
 * 的後面。
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
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        if (list1 == nullptr) { // list1為空直接return list2
            return list2;
        }

        ListNode *dummy = new ListNode(0, list1);
        list1 = dummy; // list1->next為合併後的linked list head

        while (dummy->next != nullptr && list2 != nullptr) {
            if (list2->val < dummy->next->val) {
                // 將兩個list的next存起來
                ListNode *dummy_next = dummy->next;
                ListNode *list2_next = list2->next;

                /// 將list2插入到dummy後
                dummy->next = list2;
                dummy->next->next = dummy_next;

                // list2往後一個node
                list2 = list2_next;
            }
            // dummy往後一個node
            dummy = dummy->next;
        }

        // 如果list2還有剩餘的node則將其插入到list1後
        if (list2 != nullptr) {
            while (dummy->next != nullptr) {
                dummy = dummy->next;
            }
            dummy->next = list2;
        }

        return list1->next;
    }
};

int main() {

    return 0;
}