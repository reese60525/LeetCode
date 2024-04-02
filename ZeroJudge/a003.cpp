#include <iostream>
using namespace std;

int fun(int x, int y)
{
    return (x * 2 + y) % 3;
}

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int a, b;
    while (cin >> a >> b)
    {
        switch (fun(a, b))
        {
        case 0:
            cout << "普通" << endl;
            break;
        case 1:
            cout << "吉" << endl;
            break;
        case 2:
            cout << "大吉" << endl;
            break;
        default:
            break;
        }
    }
    return 0;
}