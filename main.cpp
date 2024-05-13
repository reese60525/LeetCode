#include "myBST.h"
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    myBST *head = new myBST(5);

    for (int i = 0; i <= 10; i += 2) {
        head->insertNode(head, i);
    }
    for (int i = 1; i <= 10; i += 2) {
        head->insertNode(head, i);
    }
    head->inOrder(head);
    std::cout << '\n';

    char op;
    while (std::cin >> op) {
        int n;

        if (op == 'i') { // insert
            std::cin >> n;
            if (head == nullptr) {
                head = new myBST(n);
            }
            else if (head->insertNode(head, n) == nullptr) {
                std::cout << "重複數字:" << n << '\n';
            }
        }
        else if (op == 'd') { // delete
            std::cin >> n;
            if (head != nullptr) {
                head = head->deleteNode(head, n);
            }
        }
        else if (op == 'f') { // find
            std::cin >> n;
            if (head != nullptr) {
                if (head->findNode(head, n) == nullptr) {
                    std::cout << "找不到數字:" << n << '\n';
                }
                else {
                    std::cout << "找到node:" << head->findNode(head, n) << ", 數字:" << n << '\n';
                }
            }
        }
        else if (op == 'e') { // exit
            break;
        }
        if (head != nullptr) {
            head->inOrder(head);
            std::cout << '\n';
            std::cout << "ROOT:" << head->getValue() << '\n';
            std::cout << "head:" << head << '\n';
        }
        else {
            std::cout << "head = nullptr" << '\n';
        }
    }
    return 0;
}