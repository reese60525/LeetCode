#include <cmath>
#include <iostream>

using namespace std;
int reverse(int x) {
    int is_negative = 1, ans = 0;
    if (x == -2147483648)
        return 0;
    if (x < 0) {
        is_negative = -1;
        x *= -1;
    }

    if (int(x / pow(10, 9)) > 0) {
        for (int i = 9; i >= 0; --i) {
            if (int(x / pow(10, 9 - i)) % 10 > int(INT_MAX / pow(10, i)) % 10) {
                return 0;
            } else if (int(x / pow(10, 9 - i)) % 10 < int(INT_MAX / pow(10, i)) % 10) {
                break;
            }
        }
    }

    while (x > 0) {
        ans = (ans * 10) + (x % 10);
        x /= 10;
    }
    return ans * is_negative;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int x;
    while (cin >> x) {
        cout << reverse(x) << endl;
    }
    return 0;
}