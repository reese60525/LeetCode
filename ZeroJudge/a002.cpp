#include <iostream>
using namespace std;

int sum(int x, int y)
{
    return x + y;
}

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int a, b;
    while (cin >> a >> b)
    {
        cout << sum(a, b) << endl;
    }
    return 0;
}