#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

void fun(vector<int> input, int sum)
{
    if ((input[0] + input[3]) * 2 == sum)
        cout << input[0] + (input[1] - input[0]) * 4 << endl;
    else
        cout << input[0] * pow((input[1] / input[0]), 4) << endl;
}

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int count;
    cin >> count;
    for (int i = 0; i < count; ++i)
    {
        int a, sum = 0;
        vector<int> input;
        for (int j = 0; j < 4; ++j)
        {
            cin >> a;
            input.push_back(a);
            sum += a;
            cout << a << " ";
        }
        fun(input, sum);
    }
    return 0;
}