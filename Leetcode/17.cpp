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
    // 總共輸出次數 ex: digits = "234",共有3*3*3個輸出
    for (int i = 0; i < digits.length(); ++i) {
        len *= phone_table[(digits[i] - '0')].size();
    }
    for (int i = 0; i < len; ++i) {
        std::string temp = "";
        int len_temp = len;
        for (int j = 0; j < digits.length(); ++j) {
            len_temp /= phone_table[digits[j] - '0'].size(); // len_temp = 幾次一循環
            int digits_num = digits[j] - '0';
            temp += phone_table[digits_num][(i / len_temp) % (phone_table[digits_num].size())];
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

// backtracking algorithm 記憶體使用量大
// #include <iostream>
// #include <string>
// #include <vector>

// static const auto io_sync_off = []() {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     return nullptr;
// }();

// std::vector<std::string> ans;
// std::vector<std::string> phone_table {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

// void backtracking(std::string digits, std::string temp) {
//     // 一個answer完成，存進vector
//     if (digits.empty()) {
//         // std::cout << temp << ' '; // 印出結果
//         ans.push_back(temp);
//         return;
//     }
//     // 從digits[0]開始，每個維度對應不同的digits
//     for (auto letter : phone_table[digits[0] - '2']) {
//         backtracking(digits.substr(1), temp + letter); // substr(1): digits會從index1到end傳進function
//     }
//     return;
// }

// std::vector<std::string> letterCombinations(std::string digits) {
//     if (digits.length() == 0) {
//         return {};
//     }
//     backtracking(digits, "");
//     return ans;
// }

// int main() {
//     std::string input;
//     std::cin >> input;
//     letterCombinations(input);
//     return 0;
// }