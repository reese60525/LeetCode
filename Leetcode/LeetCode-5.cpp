#include <iostream>
using namespace std;

string longestPalindrome(string s) {
    int max[2] = {1, 1}, index_begin[2] = {0, 0}, index_end[2] = {0, 0};
    for (int i = 0; i < s.length(); ++i) {
        // 處理odd (ex:aba)
        int count = 1;
        while (true) {
            if ((i - count < 0 || i + count >= s.length()) || (s[i - count] != s[i + count])) {
                int now_count = 2 * (count - 1) + 1;
                if (now_count > max[0]) {
                    index_begin[0] = i - (count - 1);
                    index_end[0] = i + (count - 1);
                    max[0] = now_count;
                }
                break;
            }
            ++count;
        }
        // 處理even (ex:aa)
        count = 1;
        while (true) {
            if ((i - count + 1 < 0 || i + count >= s.length()) ||
                (s[i - count + 1] != s[i + count])) {
                int now_count = 2 * (count - 1);
                if (now_count > max[1]) {
                    index_begin[1] = i - (count - 2);
                    index_end[1] = i + (count - 1);
                    max[1] = now_count;
                }
                break;
            }
            ++count;
        }
    }
    // 選max大的
    string ans = "";
    if (max[1] > max[0]) {
        index_begin[0] = index_begin[1];
        index_end[0] = index_end[1];
    }
    for (int i = index_begin[0]; i <= index_end[0]; ++i) {
        ans += s[i];
    }
    return ans;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string s;
    while (cin >> s) {
        cout << longestPalindrome(s) << endl;
    }
    return 0;
}