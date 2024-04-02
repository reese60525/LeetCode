#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int w;
    double h;
    while (cin >> w >> h)
    {
        cout << fixed << setprecision(1) << w / h / h << endl;
    }
    return 0;
}