#include <iostream>
#include <string>
using namespace std;

char roman_numerals1[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
string roman_numerals2[6] = {"IV", "IX", "XL", "XC", "CD", "CM"};
int arabic_numerals1[7] = {1, 5, 10, 50, 100, 500, 1000};
int arabic_numerals2[6] = {4, 9, 40, 90, 400, 900};

int findNum(char ch)
{
    for (int i = 0; i < 7; ++i)
        if (ch == roman_numerals1[i])
            return arabic_numerals1[i];
    return 0;
}

int RomanToArabic(string input[2])
{
    int num[2] = {0, 0};
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < input[i].size(); ++j)
        {
            if (findNum(input[i][j]) < findNum(input[i][j + 1]) && (j + 1) < input[i].size())
            {
                num[i] += findNum(input[i][j + 1]) - findNum(input[i][j]);
                ++j;
            }
            else
                num[i] += findNum(input[i][j]);
        }
    }
    return abs(num[0] - num[1]);
}

void ArabicToRoman(int sum)
{
    for (int i = 6; i >= 0; --i)
    {
        int count = sum / arabic_numerals1[i];
        while (count > 0)
        {
            sum %= arabic_numerals1[i];
            cout << roman_numerals1[i];
            --count;
        }
        if (i - 1 >= 0)
        {
            int count = sum / arabic_numerals2[i - 1];
            while (count > 0)
            {
                sum %= arabic_numerals2[i - 1];
                cout << roman_numerals2[i - 1];
                --count;
            }
        }
    }
    cout << endl;
}

int main()
{
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    string input[2];
    while (cin >> input[0] >> input[1])
    {
        // fun(input);
        int sum = RomanToArabic(input);
        if (sum == 0)
            cout << "ZERO" << endl;
        else
            ArabicToRoman(sum);
    }
    return 0;
}