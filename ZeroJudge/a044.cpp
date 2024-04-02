#include <iostream>
using namespace std;

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int n;
    while (cin >> n)
        cout << (n * (n * n + 5)) / 6 + 1 << endl; // 公式 =  ( k*(k^2 + 5) ) / 6 + 1
    return 0;
}