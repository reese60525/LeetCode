#include <iostream>
using namespace std;

//  Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    ListNode *first_l1 = new ListNode;
    first_l1 = l1;
    int a = 0; // a:進位
    while (true)
    {
        int temp1 = l1->val, temp2 = l2->val;
        l1->val = (l1->val + l2->val + a) % 10;
        // cout << "temp1= " << temp1 << ", tmep2= " << temp2 << ", a_before= " << a;
        ((temp1 + temp2 + a) >= 10) ? a = 1 : a = 0;
        // cout << ", a_after= " << a << endl;
        if (l1->next == NULL || l2->next == NULL)
            break;
        l1 = l1->next;
        l2 = l2->next;
    }
    if (l1->next != NULL && l2->next == NULL)
    {
        l1 = l1->next;
        while (true)
        {
            int temp = l1->val;
            l1->val = (l1->val + a) % 10;
            ((temp + a) >= 10) ? a = 1 : a = 0;
            if (l1->next == NULL)
                break;
            l1 = l1->next;
        }
    }
    else if (l1->next == NULL && l2->next != NULL)
    {
        l2 = l2->next;
        while (true)
        {
            ListNode *newNode = new ListNode;
            newNode->next = NULL;
            l1->next = newNode;
            l1 = l1->next;
            l1->val = (l2->val + a) % 10;
            ((l2->val + a) >= 10) ? a = 1 : a = 0;
            if (l2->next == NULL)
                break;
            l2 = l2->next;
        }
    }
    // cout << "a= " << a << endl;
    if (a == 1)
    {
        ListNode *newNode = new ListNode;
        newNode->next = NULL;
        l1->next = newNode;
        l1 = l1->next;
        l1->val = 1;
    }
    return first_l1;
}

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    ListNode *l1 = new ListNode, *l2 = new ListNode, *l1_head = new ListNode, *l2_head = new ListNode;
    l1_head = l1;
    l2_head = l2;
    int a[] = {2, 4, 3, 4}, b[] = {5, 6, 4, 8};
    for (int i = 0; i < 4; ++i)
    {
        l1->val = a[i];
        l2->val = b[i];
        if (i < 3)
        {
            l1->next = new ListNode;
            l2->next = new ListNode;
            l1->next->next = NULL;
            l2->next->next = NULL;
        }
        l1 = l1->next;
        l2 = l2->next;
    }

    l1 = l1_head;
    cout << "l1:";
    while (true)
    {
        cout << l1->val << ", ";
        if (l1->next == NULL)
            break;
        l1 = l1->next;
    }
    l2 = l2_head;
    cout << "\r\nl2:";
    while (true)
    {
        cout << l2->val << ", ";
        if (l2->next == NULL)
            break;
        l2 = l2->next;
    }
    cout << endl;
    ListNode *l3 = new ListNode;
    l3 = addTwoNumbers(l1_head, l2_head);
    cout << "l3:";
    while (true)
    {
        cout << l3->val << ", ";
        if (l3->next == NULL)
            break;
        l3 = l3->next;
    }
    return 0;
}