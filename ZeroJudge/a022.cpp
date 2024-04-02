#include <iostream>
using namespace std;

string fun(string input) {
    for (int i = 0; i < input.length() / 2; ++i) {

        if (input[i] != input[input.length() - 1 - i])
            return "no";
    }
    return "yes";
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string input;
    while (cin >> input) {
        cout << fun(input) << endl;
    }
    return 0;
}