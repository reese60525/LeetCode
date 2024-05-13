#include <iostream>
using namespace std;

bool isValid(string s)
{
    char sign[] = {'(', ')', '{', '}', '[', ']'};
    int sign_count[] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < s.length(); ++i) // 預處理字串，把()和{}和[]刪掉
        if (s[i] == '(' && s[i + 1] == ')' || s[i] == '{' && s[i + 1] == '}' || s[i] == '[' && s[i + 1] == ']')
        {
            s.erase(i, 2);
            --i;
        }
    cout << "s: " << s << endl;
    for (int i = 0; i < s.length(); ++i)
        for (int j = 0; j < 6; ++j)
            if (s[i] == sign[j])
            {
                ++sign_count[j];
                if (j % 2 == 0 && s[i + 1] != sign[j + 1] && s[i + 1] != '(' && s[i + 1] != '{' && s[i + 1] != '[') // ex:(],{)
                    return false;
                if (j % 2 == 1 && sign_count[j] > sign_count[j - 1]) // 當前右括號的數量比左括號小就false,ex:(()))(
                    return false;
                break;
            }
    if (sign_count[0] != sign_count[1] || sign_count[2] != sign_count[3] || sign_count[4] != sign_count[5]) // 左右括號數量不相等
        return false;
    return true;
}

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string input;
    while (cin >> input)
        cout << isValid(input) << endl;
    return 0;
}