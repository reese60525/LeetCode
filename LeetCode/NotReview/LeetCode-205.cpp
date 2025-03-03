#include <iostream>
#include <map>
using namespace std;

bool isIsomorphic(string s, string t) {
    map<char, char> char_Correspondence;
    map<char, bool> is_usedChar;
    for (int i = 0; i < s.length(); ++i) {
        if (char_Correspondence[s[i]] == t[i]) {
            continue;
        }
        if (char_Correspondence[s[i]] == '\0' && !is_usedChar[t[i]]) {
            char_Correspondence[s[i]] = t[i];
            is_usedChar[t[i]] = true;
            continue;
        }
        return false;
    }
    return true;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string s, t;
    while (cin >> s >> t) {
        if (isIsomorphic(s, t))
            cout << "true" << endl;
        else
            cout << "false" << endl;
    }
    return 0;
}