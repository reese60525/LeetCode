#include <iostream>

using namespace std;

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
int lengthOfLastWord(string s) {
    bool check = false;
    int ans = 0;
    for (int i = s.length() - 1; i >= 0; --i) {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
            cout << s[i] << '\n';
            check = true;
        } else if (check) {
            break;
        }
        if (check) {
            ++ans;
        }
    }
    return ans;
}

int main() {
    string input;
    while (cin >> input) {
        cout << lengthOfLastWord(input) << '\n';
    }
    return 0;
}