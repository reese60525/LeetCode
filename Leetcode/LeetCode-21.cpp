#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
};

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
{
    ListNode *ans = new ListNode, *ans_head = ans;
    if (list1 == NULL) // 空的linked list回傳另一個linked list
        return list2;
    else if (list2 == NULL)
        return list1;
    while (true)
    {
        if (list1->val > list2->val)
        {
            ans->next = list2;
            list2 = list2->next;
        }
        else
        {
            ans->next = list1;
            list1 = list1->next;
        }
        if (list1 == NULL)
        {
            ans->next->next = list2;
            break;
        }
        else if (list2 == NULL)
        {
            ans->next->next = list1;
            break;
        }
        else
            ans = ans->next;
    }
    return ans_head->next; // ans_head為空，從第二個開始
}

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    ListNode *list1 = new ListNode, *list2 = new ListNode, *list1_head = list1, *list2_head = list2;
    cout << "\r\nlist1_address: " << list1_head << ", list1_next: " << list1->next << ", list1_val: " << list1_head->val << endl;
    list1->next = NULL;
    list2->next = NULL;
    int x = 3, y = 3;
    for (int i = 0; i < x; ++i)
    {
        if (i < x - 1)
        {
            list1->next = new ListNode;
            list1->next->next = NULL;
        }
        cin >> list1->val;
        list1 = list1->next;
    }
    // while (list1_head != NULL)
    // {
    //     cout << "ans_address: " << list1_head << ", ans_nest" << list1->next << ", ans_val: " << list1_head->val << endl;
    //     list1_head = list1_head->next;
    // }
    for (int i = 0; i < y; ++i)
    {
        if (i < y - 1)
        {
            list2->next = new ListNode;
            list2->next->next = NULL;
        }
        cin >> list2->val;
        list2 = list2->next;
    }
    // while (list2_head != NULL)
    // {
    //     cout << "ans_address: " << list2_head << ", ans_val: " << list2_head->val << endl;
    //     list2_head = list2_head->next;
    // }
    ListNode *ans;
    ans = mergeTwoLists(list1_head, list2_head);
    while (ans != NULL)
    {
        cout << "ans_address: " << ans << ", ans_val: " << ans->val << endl;
        ans = ans->next;
    }
    return 0;
}