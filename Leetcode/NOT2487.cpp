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
    ListNode *removeNodes(ListNode *head) {
        ListNode *ans = new ListNode, *pre = new ListNode, *max_address_head = new ListNode, *max_address_end = new ListNode,
                 *temp = new ListNode;
        temp = head;
        int max_value = 0;
        bool first = true;
        while (temp != nullptr) {
            if (max_value < temp->val) {
                max_value = temp->val;
                max_address_head = temp;
                max_address_end = temp;
            }
            else if (max_value == temp->val) {
                max_address_head->next = temp;
                max_address_end = temp;
            }
            if (temp->next == nullptr) {
                if (first) {
                    ans = max_address_head;
                    first = false;
                }
                pre->next = max_address_head;
                pre = max_address_end;
                temp = max_address_end;
                max_value = 0;
            }
            temp = temp->next;
        }
        return ans;
    }
};
int main() { return 0; }