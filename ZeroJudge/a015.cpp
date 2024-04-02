#include <iostream>
#include <vector>
using namespace std;

void fun(int r, int c)
{
    vector<int> output[c];
    int temp;
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
        {
            cin >> temp;
            output[j].push_back(temp);
        }
    for (int i = 0; i < c; ++i)
    {
        for (int j = 0; j < r; ++j)
            cout << output[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int r, c;
    while (cin >> r >> c)
        fun(r, c);
    return 0;
}