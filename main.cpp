/*
 * 解法:
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

void add(std::string num1, std::string num2) {
    int num_size1 = num1.length(), num_size2 = num2.length(), carry = 0;
    std::string ans = "";

    while (num_size1 > 0 && num_size2 > 0) {
        --num_size1;
        --num_size2;
        int n = num1[num_size1] + num2[num_size2] - ('0' * 2) + carry;
        carry = n / 10;
        n %= 10;
        ans += (n + '0');
    }
    if (num1.length() > num2.length()) {
        for (int i = num1.length() - num2.length() - 1; i > -1; --i) {
            int n = num1[i] - '0' + carry;
            carry = n / 10;
            n %= 10;
            ans += (n + '0');
        }
    }
    else if (num1.length() > num2.length()) {}
    else {
        ans += '1';
    }
    if (carry == 1)
        ans += '1';
}
// 11555 666 = 12221
void sub(std::string num1, std::string num2) {}
void mul(std::string num1, std::string num2) {}
void div(std::string num1, std::string num2) {}

int main() {
    char op;
    std::string num1, num2;
    while (std::cin >> num1 >> op >> num2) {
        if (op == '+')
            add(num1, num2);
        else if (op == '-')
            sub(num1, num2);
        else if (op == '*')
            mul(num1, num2);
        else if (op == '\\')
            div(num1, num1);
    }
    return 0;
}