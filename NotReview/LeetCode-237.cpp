#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
// 超低能題目，解法就是把下個node的值複製到當前node，然後進到下下個node。
// EX； 1->3->5->7，要刪掉7，流程:1->5->5->7，把node->next改為值為7的node，就會變成1->5->7。
class Solution {
  public:
    void deleteNode(ListNode *node) {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};
int main() { return 0; }