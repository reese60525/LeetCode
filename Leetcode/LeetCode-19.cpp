#include <iostream>
#include <vector>
using namespace std;

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

ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode *temp = head;
    int count = 0;
    while (temp != nullptr) {
        ++count;
        temp = temp->next;
    }
    // count-(n+1)被刪除的node的前一個node
    // count-(n-1)被刪除的node的後一個node
    if (count - (n + 1) < 0) {
        return head->next;
    }
    temp = head;
    for (int i = 0; i < count - n - 1; ++i) {
        temp = temp->next;
    }
    if (n == 1) {
        temp->next = nullptr;
    } else {
        temp->next = temp->next->next;
    }
    return head;
}

int main() {
    ListNode *input = new ListNode, *input_head;
    input_head = input;
    int num_input[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    // int num_input[] = {1, 2};
    for (int i = 0; i < size(num_input); ++i) {
        input->val = num_input[i];
        if (i < size(num_input) - 1) {
            input->next = new ListNode;
            input->next->next = nullptr;
        }
        input = input->next;
    }
    ListNode *ans = removeNthFromEnd(input_head, 3);
    while (ans != nullptr) {
        cout << ans->val << " ";
        ans = ans->next;
    }
    return 0;
}