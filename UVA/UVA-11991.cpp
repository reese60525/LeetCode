/*
 * 題目:https://reurl.cc/XGmQre
 * 解法:
 * 在輸入的array的同時建立hash table，之後再判斷後面輸入的問題在table是否存在。
 */

// 寫法2:用vector當table容器
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        std::vector<std::vector<int>> table(1000000); // 分配row的size
        for (int i = 0; i < n; ++i) {
            int num;
            std::cin >> num;
            table[num].emplace_back(i + 1); // table[num]依序存放每次num出現的index
        }
        for (int i = 0; i < m; ++i) {
            int num, k;
            std::cin >> k >> num;
            if (table[num].size() < k) // k是出現次數，若table[num]的size比k小代表num沒出現過這麼多次
                std::cout << 0 << '\n';
            else
                std::cout << table[num][k - 1] << '\n';
        }
    }
    return 0;
}
// //寫法1:用unordered_map當table容器
// #include <iostream>
// #include <unordered_map>
// #include <vector>

// static const auto io_sync_off = []() {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     return nullptr;
// }();

// int main() {
//     int n, m;
//     while (std::cin >> n >> m) {
//         std::unordered_map<int, std::unordered_map<int, int>> table;
//         std::unordered_map<int, int> occurrence_count;// 用來計算num的出現次數
//         for (int i = 0; i < n; ++i) {
//             int num;
//             std::cin >> num;
//             ++occurrence_count[num];
//             table[num][occurrence_count[num]] = i + 1;
//         }
//         while (m--) {
//             int num, k;
//             std::cin >> k >> num;
//             if (table[num][k] == 0)
//                 std::cout << 0 << '\n';
//             else
//                 std::cout << table[num][k] << '\n';
//         }
//     }
//     return 0;
// }