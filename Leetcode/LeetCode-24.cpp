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
        // link_list 為空或只有一個node
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *pre = new ListNode, *now = new ListNode;
        now = head;
        // return的head為第二個node
        head = head->next;
        // 千萬要小心別使用到空指標
        while (now != nullptr && now->next != nullptr) {
            pre->next = now->next;
            now->next = now->next->next;
            pre->next->next = now; // 如果是now->next->next是錯誤的，因為now->next的值已經在上一行改了!
            pre = now;
            now = now->next;
        }
        return head;
    }
};

int main() {
    Solution solution;
    ListNode *head = new ListNode, *new_head = new ListNode;
    new_head = head;
    int nums[] {1, 2, 3, 4};
    for (int i = 0; i < 4; ++i) {
        head->val = nums[i];
        if (i == 3) {
            head->next = nullptr;
            break;
        }
        ListNode *new_node = new ListNode;
        head->next = new_node;
        head = head->next;
    }
    solution.swapPairs(new_head);
    return 0;
}