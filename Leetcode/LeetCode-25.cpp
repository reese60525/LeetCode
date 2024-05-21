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
    ListNode *ans = new ListNode, *begin = new ListNode(-1),
             *next = new ListNode(-1), *pre = new ListNode(-1);
    bool does_get_ans = false;
    while (head) {
      ListNode *check = new ListNode;
      check = head;
      // check剩下的node夠不夠reverse
      for (int i = 1; i < k; ++i) {
        check = check->next;
        if (check == nullptr)
          return ans;
      }
      // build return_head
      if (!does_get_ans) {
        ans = check;
        does_get_ans = true;
      }
      // 開始reverse
      begin->next = check;
      begin = head;
      next = head->next;
      for (int i = 1; i < k; ++i) {
        pre = head;
        head = next;
        next = head->next;
        head->next = pre;
      }
      begin->next = next;
      head = next;
    }
    return ans;
  }
};
int main() {
  Solution solution;
  ListNode *head = new ListNode, *new_head = new ListNode,
           *return_node = new ListNode;
  new_head = head;
  int k = 4, nums[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < sizeof(nums) / 4; ++i) {
    head->val = nums[i];
    if (i == sizeof(nums) / 4 - 1) {
      head->next = nullptr;
      break;
    }
    ListNode *new_node = new ListNode;
    head->next = new_node;
    head = head->next;
  }
  return_node = solution.reverseKGroup(new_head, k);
  while (return_node != nullptr) {
    std::cout << return_node << ", " << return_node->val << '\n';
    return_node = return_node->next;
  }
  return 0;
}