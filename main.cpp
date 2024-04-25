#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int recursive_solve(int index, int max_len, std::vector<std::string> co_string) {}

int longestIdealString(std::string s, int k) {
    int max_length = 0, s_index = s.length() - 1;
    std::vector<std::string> co_string;
    int co_size = 1;
    char co_begin, co_end;
    // acfgbd 2
    while (s_index >= 0) {
        if (co_size == 1) {
            co_end = s[s_index];
        }
        if (s_index == 0 || abs(s[s_index] - s[s_index - 1]) > k) {
            std::string temp = "";
            co_begin = s[s_index];
            temp += std::to_string(co_size) + co_begin + co_end;
            co_string.push_back(temp);
            co_size = 1;
            --s_index;
        }
        else {
            ++co_size;
            --s_index;
        }
    }
    sort(co_string.begin(), co_string.end());
    for (auto i : co_string) {
        recursive_solve(i, co_string[i][0] - '0', co_string);
    }
    // for (auto i : co_string) {
    //     std::cout << i << '\n';
    // }
    // abbc'z'efh'z'ddd'z'jjj> abcehfjjj
    // 1zz 1zz 1zz 4ac 3eh 3dd 3jj
    return 0;
}

int main() {
    std::string s;
    int k;
    while (std::cin >> s >> k) {
        longestIdealString(s, k);
    }
    return 0;
}