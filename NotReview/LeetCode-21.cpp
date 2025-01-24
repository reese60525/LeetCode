/*
 * 題目： https://leetcode.com/problems/merge-two-sorted-lists/description/
 *
 * 題目解釋：
 * 給兩個sorted linked list，將兩個list合併成一個sorted linked list。
 *
 * 思路：
 * 創建一個dummy，依次比較當前list1和list2的值，將較小的node接到dummy後面，直到其中一個list
 * 做完，之後再將沒做完的list接到dummy後面。
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
        ListNode *dummy = new ListNode(0, nullptr), *cur = dummy;

        while (list1 != nullptr && list2 != nullptr) {
            // 將較小的node接到dummy後面
            if (list1->val < list2->val) {
                cur->next = list1;
                list1 = list1->next;
            }
            else {
                cur->next = list2;
                list2 = list2->next;
            }

            cur = cur->next;
        }

        // 將沒做完的list接到dummy後面
        cur->next = (list1 != nullptr) ? list1 : list2;

        return dummy->next;
    }
};

int main() {

    return 0;
}