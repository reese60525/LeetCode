/*
 * 題目： https://leetcode.com/problems/merge-k-sorted-lists/description/
 *
 * 題目解釋：
 * 給k個linked list，將所有的linked list合併成一個linked list。
 *
 * 思路：
 * 方法1:divide and conquer
 * 將lists中的link list兩兩合併，直到最後剩下一個linked list。
 *
 * 方法2:priority queue
 * 把lists中的所有list放入priority queue，該priority queue是min heap，然後將priority queue
 * 中的最小node(min heap的最小值在top)取出並放入dummy後面，將該list往後一個node，直到priority queue
 * 為空。
 */
#include <iostream>
#include <queue>

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

// // 方法1:divide and conquer
// class Solution {
//   public:
//     ListNode *mergeKLists(std::vector<ListNode *> &lists) {
//         if (lists.empty()) {
//             return {};
//         }

//         while (lists.size() > 1) {             // 做到只剩下一個linked list
//             std::vector<ListNode *> new_lists; // 存放合併後的linked list

//             for (int i = 0; i < lists.size(); i += 2) {
//                 ListNode *list1 = lists[i];
//                 // 若lists中的linked list數量為奇數，則最後一組的linked list的list2用nullptr來代替
//                 ListNode *list2 = (i + 1 < lists.size()) ? lists[i + 1] : nullptr;
//                 // 將合併後的linked list加入new_lists
//                 new_lists.push_back(mergeTwoLists(list1, list2));
//             }
//             // 將new_lists複製給lists
//             lists = new_lists;
//         }

//         return lists[0];
//     }

//   private:
//     ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
//         ListNode *dummy = new ListNode(0, nullptr), *cur = dummy;

//         while (list1 != nullptr && list2 != nullptr) {
//             // 將較小的node接到dummy後面
//             if (list1->val < list2->val) {
//                 cur->next = list1;
//                 list1 = list1->next;
//             }
//             else {
//                 cur->next = list2;
//                 list2 = list2->next;
//             }
//             cur = cur->next;
//         }

//         // 將沒做完的list接到dummy後面
//         cur->next = list1 == nullptr ? list2 : list1;

//         return dummy->next;
//     }
// };

// 方法2:priority queue
class Solution {
  public:
    ListNode *mergeKLists(std::vector<ListNode *> &lists) {
        // 定義priority queue的比較函式
        auto cmp = [](ListNode *a, ListNode *b) {
            return a->val > b->val; // pq的優先判斷是!cmp，所以min heap要用「大於」
        };

        // 建立一個priority queue，並將lists中的node放入priority queue
        std::priority_queue<ListNode *, std::vector<ListNode *>, decltype(cmp)> pq;

        for (ListNode *list : lists) {
            if (list != nullptr) {
                pq.push(list);
            }
        }

        // 將priority queue中的node取出並放入dummy後面
        ListNode *dummy = new ListNode(0), *cur = dummy;
        while (!pq.empty()) {
            ListNode *node = pq.top();
            pq.pop();

            cur->next = node;
            cur = cur->next;

            node = node->next;
            if (node != nullptr) {
                pq.push(node);
            }
        }

        return dummy->next;
    }
};

int main() {

    return 0;
}