#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

struct CoStrings {
    std::vector<int> len;
    std::vector<std::string> head_tail;
};

int recursive_solve(int now_len, std::string now_head_tail, std::vector<int> len_list, std::vector<std::string> head_tail_list, int k) {
    std::cout << "----------------------------------------------" << '\n';
    std::cout << "now:" << now_len << ", " << now_head_tail << '\n';
    for (auto i : len_list)
        std::cout << i << ' ';
    std::cout << '\n';
    for (auto i : head_tail_list)
        std::cout << i << ' ';

    std::cout << "\n\n";
    int max_value = 0;
    for (int i = 0; i < head_tail_list.size(); ++i) {
        std::cout << "i=" << i << '\n';
        if (abs(now_head_tail[1] - head_tail_list[i][0]) <= k) { // 頭接now的尾
            std::cout << "in" << '\n';
            int temp_len = now_len + len_list[i];
            std::string temp_head_tail = "";
            temp_head_tail += now_head_tail[0];
            temp_head_tail += head_tail_list[i][1];
            std::cout << "temp_head_tail=" << temp_head_tail << '\n';
            len_list.erase(len_list.begin(), len_list.begin() + i + 1);
            head_tail_list.erase(head_tail_list.begin(), head_tail_list.begin() + i + 1);
            int return_value = recursive_solve(temp_len, temp_head_tail, len_list, head_tail_list, k);
            max_value = return_value > max_value ? return_value : max_value;
        }
    }
    if (max_value == 0)
        return now_len;
    else
        return max_value;
}

int longestIdealString(std::string s, int k) {
    CoStrings co_string;
    int max_length = 0, s_index = s.length() - 1;
    int co_size = 1;
    std::string co_begin, co_end;
    while (s_index >= 0) {
        std::cout << "abs=" << abs(s[s_index] - s[s_index - 1]) << '\n';
        if (co_size == 1) {
            co_end = s[s_index];
        }
        if (s_index == 0 || abs(s[s_index] - s[s_index - 1]) > k) {
            co_begin = s[s_index];
            std::string temp;
            temp = co_begin + co_end;
            co_string.len.push_back(co_size);
            co_string.head_tail.push_back(temp);
            co_size = 1;
            --s_index;
        }
        else {
            ++co_size;
            --s_index;
        }
    }

    std::reverse(co_string.len.begin(), co_string.len.end());
    std::reverse(co_string.head_tail.begin(), co_string.head_tail.end());
    for (auto i : co_string.len)
        std::cout << i << ' ';
    std::cout << '\n';
    for (auto i : co_string.head_tail)
        std::cout << i << ' ';

    std::cout << '\n';

    while (co_string.head_tail.size()) {
        int temp_len = co_string.len[0];
        std::string temp_head_tail = co_string.head_tail[0];
        co_string.len.erase(co_string.len.begin());
        co_string.head_tail.erase(co_string.head_tail.begin());
        int return_len = recursive_solve(temp_len, temp_head_tail, co_string.len, co_string.head_tail, k);
        max_length = max_length > return_len ? max_length : return_len;
    }
    // acfgbd 2
    // abbczefhzdddzjjj 2
    // abbc'z'efh'z'ddd'z'jjj > abbcehfjjj
    // 4ac 1zz 3eh 1zz 3dd 1zz 3jj
    return max_length;
}

int main() {
    std::string s;
    int k;
    while (std::cin >> s >> k) {
        std::cout << longestIdealString(s, k) << '\n';
    }
    return 0;
}
