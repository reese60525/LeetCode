#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

int fun(map<int, int> milk, vector<int> price, int n)
{
    int ans = 0;
    for (int i = 0; i < price.size() && n > 0; ++i)
    {
        if (milk[price[i]] > 0)
        {
            if (n >= milk[price[i]])
            {
                ans += milk[price[i]] * price[i];
                n -= milk[price[i]];
                milk[price[i]] = 0;
            }
            else
            {
                ans += n * price[i];
                n = 0;
                milk[price[i]] -= n;
            }
        }
    }
    return ans;
}

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m)
    {
        vector<int> price;
        map<int, int> milk;
        for (int i = 0; i < m; ++i)
        {
            int a, b;
            cin >> a >> b;
            price.push_back(a);
            milk[a] += b;
        }
        sort(price.begin(), price.end());

        // cout << "**********TEST1**********" << endl;
        // for (int i = 0; i < price.size(); ++i)
        //     cout << "price " << price[i] << ", num" << milk[price[i]] << endl;
        // cout << "**********TEST1**********" << endl;

        cout << fun(milk, price, n) << endl;
    }
    return 0;
}