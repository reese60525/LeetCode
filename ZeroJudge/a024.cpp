#include <iostream>

using namespace std;

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int a, b;
    while (cin >> a >> b) {
        // 輾轉相除法
        while (true) {
            int c = a % b;
            if (c == 0) {
                cout << b << '\n';
                break;
            }
            a = b;
            b = c;
        }
    }
    return 0;
}