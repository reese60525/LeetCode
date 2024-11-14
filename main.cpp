/*
 * 題目： https://leetcode.com/problems/merge-k-sorted-lists/description/
 *
 * 題目解釋：
 *
 * 思路：
 *
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
    ListNode *mergeKLists(std::vector<ListNode *> &lists) {
        return divideAndConquer(lists);
    }

  private:
    ListNode *divideAndConquer(std::vector<ListNode *> &lists) {
        // 遞迴終止條件
        if (lists.empty()) {
            return nullptr;
        }
        if (lists.size() == 1) {
            return lists[0];
        }

        // 分割
        int n = lists.size();
        std::vector<ListNode *> left, right;
        left.assign(lists.begin(), lists.begin() + n / 2);
        right.assign(lists.begin() + n / 2, lists.end());

        ListNode *list1 = divideAndConquer(left);
        ListNode *list2 = divideAndConquer(right);

        // 合併
        return mergeTwoLists(list1, list2);
    }

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *dummy = new ListNode(0, nullptr), *new_list = dummy;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                dummy->next = new ListNode(l1->val, nullptr);
                l1 = l1->next;
            }
            else {
                dummy->next = new ListNode(l2->val, nullptr);
                l2 = l2->next;
            }
            dummy = dummy->next;
        }

        if (l1 != nullptr) {
            dummy->next = l1;
        }
        if (l2 != nullptr) {
            dummy->next = l2;
        }

        return new_list->next;
    }
};

int main() {

    return 0;
}