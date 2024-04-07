#include <iostream>
#include <vector>
using namespace std;

string convert(string s, int numRows) {
    string ans = "";
    if (numRows == 1) {
        return s;
    }
    for (int i = 1; i <= numRows; ++i) {
        int distance = numRows - i;
        for (int j = i - 1; j < s.length(); j = j) {
            ans += s[j];
            j += distance * 2;
            if (j < s.length() && i != 1 && i != numRows) {
                ans += s[j];
            }
            j += (i - 1) * 2;
        }
    }
    return ans;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int row;
    string input;
    while (cin >> input >> row) {
        cout << convert(input, row) << endl;
    }
    return 0;
}

// num = 1
// aaaaaa

// num =2
// aaaa
// aaaa

// num = 3
// a a a
// aaaaa
// a a a

// num = 4
// a  a  a  a
// a aa aa aa
// aa aa aa a
// a  a  a  a

// num = 5
// a   a   a
// a  aa  aa
// a a a a a
// aa  aa  a
// a   a   a

// num = 8
//  a      a      a
//  a     aa     aa
//  a    a a    a a
//  a   a  a   a  a
//  a  a   a  a   a
//  a a    a a    a
//  aa     aa     a
//  a      a      a