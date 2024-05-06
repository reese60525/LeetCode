/*
 * 解法 :
 * "32"->17->16->"23"->13->"17"->"8"->3->"6"，""內的值就是題目要找的答案
 * 可以發現如果從最後一個節點往前看，要找的值永遠都大於等於上一個要找的值，因此可以
 * 從最後一個node往前找越來越大的node，最後再從開頭依序更改鏈結(next)就好。
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
    ListNode *removeNodes(ListNode *head) {
        ListNode *last = head;
        std::vector<ListNode *> ans;
        int address_diff = head - head->next; // node之間的address差，pre = now + address_diff
        while (last->next != nullptr) {
            last = last->next;
        }
        int max_value = last->val;
        while (true) {
            if (last->val >= max_value) {
                max_value = last->val;
                ans.push_back(last);
            }
            if (last == head) // 這個要後判斷，否則可能會少一個node。EX:1->1->1->1只有存到1->1->1。
                break;
            last += address_diff;
        }
        head = ans[ans.size() - 1]; // head為最後一個push進去的node
        for (int i = ans.size() - 1; i > 0; --i) {
            ans[i]->next = ans[i - 1];
        }
        ans[0]->next = nullptr; // 最後一個node指向nullptr
        return head;
    };
};
int main() { return 0; }