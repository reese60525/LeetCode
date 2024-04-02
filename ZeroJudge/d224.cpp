#include <iostream>
using namespace std;

int main() {
    // cin.sync_with_stdio(false);
    // cin.tie(nullptr);
    int n;
    while ((cin >> n)) {
        n /= 2;
        cout << (long long)(n + 2) * (n + 1) / 2 << endl; // 方法數會超過int範圍，要先變成long long
    }
    return 0;
}