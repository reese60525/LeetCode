// 題目:https://vjudge.net/contest/277912#problem/A

#include <iostream>
#include <sstream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int findRoot(int computer_list[], int n) {
    while (computer_list[n] != n) {
        n = computer_list[n];
    }
    return n;
}

int main() {
    int n; // n筆測資
    std::cin >> n;
    while (n--) {
        int computer_nums, is_connected[2] = {0, 0};
        // 輸入電腦數量
        std::cin >> computer_nums;
        // 初始化每台電腦的root
        int *computer_list = new int[computer_nums + 1];
        for (int i = 1; i <= computer_nums; ++i) {
            computer_list[i] = i;
        }
        std::string input;
        std::cin.ignore();
        while (getline(std::cin, input) && input != "") {
            std::stringstream k(input);
            char action;
            int computer1, computer2;
            k >> action >> computer1 >> computer2;

            if (action == 'c') {
                // 兩台電腦的root不需要比大小，把誰為新root並不影響答案和速度
                computer_list[findRoot(computer_list, computer1)] = findRoot(computer_list, computer2);
            }
            else {
                if (findRoot(computer_list, computer1) == findRoot(computer_list, computer2))
                    ++is_connected[0];
                else
                    ++is_connected[1];
            }
        }
        std::cout << is_connected[0] << "," << is_connected[1] << "\n";
        if (n > 0)
            std::cout << '\n';
    }
    return 0;
}