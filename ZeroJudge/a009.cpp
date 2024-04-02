#include <iostream>
using namespace std;

void fun(string input)
{
    int k = 7;
    for (int i = 0; i < input.length(); ++i)
        cout << char(input[i] - 7);
    cout << endl;
}

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string input;
    while (cin >> input)
        fun(input);
    return 0;
}