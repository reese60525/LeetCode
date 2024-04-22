#include <iostream>
#include <string>

using namespace std;

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int n;
    while (cin >> n) {
        string ans = "";
        // 除以2的值繼續除直到為0，%2的餘數h存到ANS，最後倒序輸出
        while (true) {
            ans += '0' + (n % 2);
            n /= 2;
            if (n == 0)
                break;
        }
        for (int i = ans.length() - 1; i >= 0; --i)
            cout << ans[i];
        cout << '\n';
    }
    return 0;
}