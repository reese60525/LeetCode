#include <iostream>
#include <map>
using namespace std;

int romanToInt(string s) {
    map<char, int> roman = {
        {'I', 1   },
        {'V', 5   },
        {'X', 10  },
        {'L', 50  },
        {'C', 100 },
        {'D', 500 },
        {'M', 1000}
    };
    int sum = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (roman[s[i]] < roman[s[i + 1]] && i + 1 < s.length()) {
            sum += roman[s[i + 1]] - roman[s[i]];
            ++i;
        } else
            sum += roman[s[i]];
    }
    return sum;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string input;
    while (cin >> input) {
        cout << romanToInt(input) << endl;
    }
    return 0;
}

// 這方法比map快，也更省記憶體空間
// char roman_numerals[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
// int arabic_numerals[7] = {1, 5, 10, 50, 100, 500, 1000};

// int findNum(char ch)
// {
//     for (int i = 0; i < 7; ++i)
//         if (ch == roman_numerals[i])
//             return arabic_numerals[i];
//     return 0;
// }

// int romanToInt(string s)
// {
//     int sum = 0;
//     for (int i = 0; i < s.length(); ++i)
//         if (findNum(s[i]) < findNum(s[i + 1]) && (i + 1) < s.length())
//         {
//             sum += findNum(s[i + 1]) - findNum(s[i]);
//             ++i;
//         }
//         else
//             sum += findNum(s[i]);
//     return sum;
// }