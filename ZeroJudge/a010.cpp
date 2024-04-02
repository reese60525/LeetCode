#include <cmath>
#include <iostream>
using namespace std;

void fun(int input) {
    int num = input;
    for (int i = 2; i < sqrt(num) + 1; ++i) {
        if (input % i == 0) {
            int count = 0;
            while (input % i == 0) {
                ++count;
                input /= i;
            }
            cout << i;
            if (count > 1)
                cout << '^' << count;
            if (input != 1)
                cout << " * ";
        } else if (input == 1)
            break;
    }
    if (input != 1)
        cout << input;
    cout << endl;
}

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    int input;
    while (cin >> input)
        fun(input);
    return 0;
}