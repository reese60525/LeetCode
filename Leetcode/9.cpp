#include <iostream>
#include <vector>
using namespace std;

bool isPalindrome(int x)
{
    string a = to_string(x);
    if (x < 0)
        return false;
    else if (x > -1 && x < 10)
        return true;
    else
        for (int i = 0; i < a.length() / 2; ++i)
            if (a[i] != a[a.length() - 1 - i])
                return false;
    return true;
}

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int n;
    while (cin >> n)
        cout << isPalindrome(n) << endl;
    return 0;
}