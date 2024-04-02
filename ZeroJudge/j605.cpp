#include <iostream>
using namespace std;

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int n, t, s;
    while (cin >> n)
    {
        int highest_t = -1, highest_s = -1, count = 0;
        for (int i = 0; i < n; ++i)
        {
            cin >> t >> s;
            if (s == -1)
                ++count;
            else if (highest_s < s)
            {
                highest_t = t;
                highest_s = s;
            }
        }
        int ans = highest_s - n - count * 2;
        cout << ((ans > 0) ? ans : 0) << " " << highest_t << endl;
    }
    return 0;
}