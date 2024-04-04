#include <iostream>
using namespace std;

int lengthOfLongestSubstring(string s) {
    if (s.length() == 0)
        return 0;
    int char_index[200], max = 1, ansIndex_begin = 0;
    for (int i = 0; i < 200; ++i) {
        char_index[i] = -1;
    }
    char_index[s[0]] = 0;
    for (int i = 1; i < s.length(); ++i) {
        if (char_index[s[i]] >= ansIndex_begin) {
            if (i - ansIndex_begin > max) {
                max = i - ansIndex_begin;
            }
            ansIndex_begin = char_index[s[i]] + 1;
        }
        char_index[s[i]] = i;
    }
    if ((s.length() - ansIndex_begin) > max)
        return (s.length() - ansIndex_begin);
    else
        return max;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string input;
    while (cin >> input) {
        cout << lengthOfLongestSubstring(input) << endl;
    }
    return 0;
}