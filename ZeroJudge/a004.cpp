#include <iostream>
using namespace std;

void fun(int x)
{
    if (x % 4 == 0 && x % 100 != 0 || x % 400 == 0)
        cout << "閏年" << endl;
    else
        cout << "平年" << endl;
}
int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int a;
    while (cin >> a)
        fun(a);
}