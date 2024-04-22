#include <iostream>
#include <string>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
std::vector<std::string> letterCombinations(std::string digits) {
    int len = 1;
    std::vector<std::string> ans;
    std::vector<std::vector<char>> phone_table {
        {},
        {},
        {'a', 'b', 'c'},
        {'d', 'e', 'f'},
        {'g', 'h', 'i'},
        {'j', 'k', 'l'},
        {'m', 'n', 'o'},
        {'p', 'q', 'r', 's'},
        {'t', 'u', 'v'},
        {'w', 'x', 'y', 'z'}
    };
    if (digits.length() == 0) {
        return ans;
    }
    for (int i = 0; i < digits.length(); ++i) {
        len *= phone_table[(digits[i] - '0')].size();
    }
    // 111111111 9
    // 444555666 3
    // 789789789 1
    for (int i = 0; i < len; ++i) {
        std::string temp = "";
        int len_temp = len;
        for (int j = 0; j < digits.length(); ++j) {
            len_temp /= phone_table[digits[j] - '0'].size();
            temp += phone_table[digits[j] - '0'][(i / len_temp) % (phone_table[digits[j] - '0'].size())];
        }
        std::cout << temp << " ";
        ans.push_back(temp);
    }
    return ans;
}

int main() {
    std::string input;
    std::cin >> input;
    letterCombinations(input);
    return 0;
}
