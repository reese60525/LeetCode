#include <iostream>
using namespace std;

void fun(int max[4]) { max[2] = -1; }

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int max[4] = {1, 2, 3, 4};
    fun(max);
    for (int i = 0; i < 4; ++i) {
        cout << max[i] << " ";
    }
    return 0;
}