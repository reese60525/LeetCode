#include <iostream>
#include <vector>
using namespace std;

string removeStars(string s) {
    int index = 0;
    string ans = "";
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '*') {

        } else {
            ans += s[i];
            ++index;
        }
    }
    string ans = "";
    for (int i = 0; i < temp.size(); ++i) {
        ans += temp[i];
    }
    return ans;
}
int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string input;
    while (cin >> input) {
        cout << removeStars(input) << endl;
    }
    return 0;
}