#include <iostream>

using namespace std;

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

string intToRoman(int num) {
    string roman_list[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
    int arabic_list[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
    int counter = 12;
    string ans = "";
    while (num > 0) {
        int temp = num / arabic_list[counter];
        for (int i = 0; i < temp; ++i) {
            ans += roman_list[counter];
        }
        num %= arabic_list[counter];
        --counter;
    }
    return ans;
}

int main() {
    int num;
    while (cin >> num) {
        cout << intToRoman(num) << '\n';
    }
    return 0;
}