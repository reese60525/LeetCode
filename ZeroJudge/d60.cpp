#include <iostream>

using namespace std;

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int a;
    while (cin >> a) {
        cout << (60 - (a - 25)) % 60 << '\n';
    }
    return 0;
}