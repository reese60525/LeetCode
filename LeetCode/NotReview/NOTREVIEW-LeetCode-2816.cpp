/*
 * 解法1:
 * 遍歷list把value存進nums[]，之後一個個做乘2運算，最後再遍歷一次list，update value。
 *
 * 解法2:
 * 判斷當前node的value*2之後是否大於8(0~4乘以2為0~8，不用進位)，若大於8則把前一個node
 * 的value+1，由於乘以2對10的餘數最多為8，所以pre node的value+1不可能進位，以此方式遍歷
 * 整個list。
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
// 遍歷一次就好，
class Solution {
  public:
    ListNode *doubleIt(ListNode *head) {
        ListNode *cur = head, *pre = nullptr;
        while (cur != nullptr) {
            cur->val *= 2;
            if (cur->val > 8) {       // 0~4乘以2是0~8，5~9乘以2是10~18
                if (pre == nullptr) { // 處理head->val=5~9時要新建node
                    pre = new ListNode(0);
                    pre->next = cur;
                    head = pre;
                }
                cur->val %= 10;
                pre->val += 1;
            }
            pre = cur;
            cur = cur->next;
        }
        return head;
    }
};
// // 要遍歷兩次+使用size為10000的array(測資最大size)
// class Solution {
//   public:
//     ListNode *doubleIt(ListNode *head) {
//         int nums[10001], count = 0;
//         ListNode *now = head;
//         memset(nums, 0x3f, sizeof(nums));
//         while (now != nullptr) {
//             nums[count] = now->val;
//             ++count;
//             now = now->next;
//         }
//         // 乘以二
//         int carry = 0;
//         for (int i = count - 1; i >= 0; --i) {
//             nums[i] <<= 1;
//             nums[i] += carry;
//             carry = nums[i] / 10;
//             nums[i] %= 10;
//         }
//         // 考慮500*2=1000這種情況
//         now = head;
//         if (carry == 1) {
//             ListNode *node = new ListNode(1);
//             node->next = now;
//             head = node;
//         }
//         // update list value
//         for (int i = 0; i < count; ++i) {
//             now->val = nums[i];
//             now = now->next;
//         }
//         return head;
//     }
// };
int main() { return 0; }