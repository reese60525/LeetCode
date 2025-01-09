/*
 *  Author      : Reese
 *  Created On  : 2025-01-02 10:12
 *  Description : https://leetcode.com/problems/my-calendar-i/description/
 */

#include <iostream>
#include <set>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 使用 std::set
class MyCalendar {
  private:
    std::set<std::pair<int, int>> event;

  public:
    MyCalendar() {}

    bool book(int startTime, int endTime) {
        // 使用 lower_bound 找到第一個大於等於 endTime 的 iterator
        const auto it = event.lower_bound({endTime, 0});
        // 如果 event 為空，或是 it 的前一個區間的 endTime 小於等於 startTime，則可以插入
        if (it == event.begin() || startTime >= prev(it)->second) {
            event.emplace(startTime, endTime);
            return true;
        }
        return false;
    }
};

// // 手寫 binary tree
// struct Node {
//     int start, end;
//     Node *left, *right;
//     Node(int st, int ed) : start(st), end(ed), left(nullptr), right(nullptr) {};
// };

// class MyCalendar {
//   private:
//     Node *root;

//   public:
//     // 初始化 root 為 nullptr
//     MyCalendar() : root(nullptr) {}

//     // 搜尋 binary search tree
//     // Node *&cur 是傳入資料型態為 Node* 的 reference，而不是 temp value
//     bool dfs(int st, int ed, Node *&cur) {
//         // 在 tree 沒有任何區間跟搜尋的區間重疊
//         // 這樣修改 nullptr 能起作用是因為 cur 是 cur->left 或 cur->right 的 reference
//         if (cur == nullptr) {
//             cur = new Node(st, ed);
//             return true;
//         }

//         // 繼續檢查其餘區間
//         if (ed <= cur->start) {
//             return dfs(st, ed, cur->left);
//         }
//         else if (st >= cur->end) {
//             return dfs(st, ed, cur->right);
//         }

//         // 搜尋的區間跟 tree 中某個區間有重疊
//         return false;
//     }

//     bool book(int startTime, int endTime) {
//         return dfs(startTime, endTime, root);
//     }
// };

int main() {

    return 0;
}