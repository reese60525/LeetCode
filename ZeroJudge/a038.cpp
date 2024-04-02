#include <iostream>
using namespace std;

string fun(string input) {
    string ans = "";
    bool check = false;
    for (int i = input.length() - 1; i >= 0; --i) {
        if (!check && input[i] == '0')
            continue;
        else if (!check && input[i] != '0')
            check = true;
        ans += input[i];
    }
    if (ans == "")
        return "0";
    else
        return ans;
}
int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string input;
    while (cin >> input) {
        cout << fun(input);
    }
    return 0;
}