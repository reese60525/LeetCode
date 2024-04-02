#include <iostream>
#include <vector>
using namespace std;

int num[26] = {10, 11, 12, 13, 14, 15, 16, 17, 34, 18, 19, 20, 21,
               22, 35, 23, 24, 25, 26, 27, 28, 29, 32, 30, 31, 33};

void fun(string input) {
    int sum = 0;
    int temp = num[input[0] - 'A'];
    sum += (temp % 10) * 9 + temp / 10;
    for (int i = 1; i < 9; ++i) {
        sum += (input[i] - '0') * (9 - i);
    }
    sum += input[9] - '0';
    if (sum % 10 == 0)
        cout << "real" << endl;
    else
        cout << "fake" << endl;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string input;
    while (cin >> input) {
        fun(input);
    }
    return 0;
}