/*
 * 題目： https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/
 *
 * 題目解釋：
 * 給一個link list和正整數n，題目要求移除link list從尾端數來第n個node，以one round來完成。
 * e.g. link list = [1,2,3,4,5] and n = 2，移除後:link list = [1,2,3,5]。
 *
 * 思路：
 * 以 link list = [1,2,3,4,5,6,7] and n = 2為例，head需要移動四次來到5，並且把5連接到7。
 * 首先將head移動n=2次後來到3，再將head移動到尾端節點7則需要恰好4步，因此用一個temp代替head，先移動n步，
 * 再將temp和head一起移動到最後一個node，此時temp在7，head在5，將head->next連接到head->next->next即可。
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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode *cur = head, *temp = head;

        while (n--) { // temp先移動n步
            temp = temp->next;
        }

        if (temp == nullptr) { // 若此時temp為nullptr，代表要刪除的node為head(第一個node)
            return head->next;
        }

        while (temp->next != nullptr) { // 同時移動temp和cur，直到temp到最後一個node
            temp = temp->next;
            cur = cur->next;
        }
        cur->next = cur->next->next;

        return head;
    }
};

int main() {

    return 0;
}