#include <algorithm>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int chicken_num, eagle, round;
    std::cin >> chicken_num;
    std::vector<int> chicken_list, eagle_list;
    // input
    while (chicken_num--) {
        int n;
        std::cin >> n;
        chicken_list.push_back(n);
    }
    std::cin >> eagle >> round;
    while (round--) {
        int n;
        std::cin >> n;
        eagle_list.push_back(n);
    }
    // output
    while (!eagle_list.empty()) {
        // 找被抓到的小雞的index
        std::vector<int>::iterator chicken_index = std::find(chicken_list.begin(), chicken_list.end(), eagle_list[0]);
        int temp = eagle_list[0];
        // data交換
        chicken_list[chicken_index - chicken_list.begin()] = eagle;
        eagle = temp;
        // 做完交換後把eagle_list-1
        eagle_list.erase(eagle_list.begin());
    }
    for (auto i : chicken_list)
        std::cout << i << " ";
    return 0;
}