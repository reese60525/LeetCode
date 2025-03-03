/*
 * 題目: https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/description/
 *
 * 題目解釋:
 * 給一個link-list，在每個相鄰node之間插入兩數的GCD。

 * 思路:
 * 用c++內建的gcd函式算出gcd後插入node之間。
 *
 * 解法:
 * 同上。
 */
#include <iostream>
#include <numeric>

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
    ListNode *insertGreatestCommonDivisors(ListNode *head) {
        ListNode *now = head;

        while (now->next != nullptr) { // 做到最後一個node後就跳出迴圈
            int a = now->val;
            int b = now->next->val;
            int gcd = std::gcd(a, b);                      // 計算兩數gcd
            ListNode *node = new ListNode(gcd, now->next); // 建立新的node
            now->next = node;                              // 插入node
            now = node->next;                              // 移到下個node
        }

        return head;
    }
};

int main() {

    return 0;
}