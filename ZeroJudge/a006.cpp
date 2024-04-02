#include <cmath>
#include <iostream>
using namespace std;

void fun(int a, int b, int c)
{
    if ((b * b - 4 * a * c) > 0)
        cout << "Two different roots x1=" << (sqrt(b * b - 4 * a * c) - b) / (2 * a) << " , x2=" << ((0 - sqrt(b * b - 4 * a * c)) - b) / (2 * a) << endl;
    else if ((b * b - 4 * a * c) == 0)
        cout << "Two same roots x=" << (0 - b) / (2 * a) << endl;
    else
        cout << "No real root" << endl;
}

int main()
{
    // cin.sbnc_with_stdio(false); cin.tie(nullptr);
    int a, b, c;
    while (cin >> a >> b >> c)
        fun(a, b, c);
    return 0;
}