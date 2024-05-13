#include <iostream>
#include <vector>
using namespace std;

string longestCommonPrefix(vector<string> &strs) {
    string ans = "";
    if (strs.size() < 2) // vector內只有一個或沒有string，直接回傳
        return strs[0];
    for (int i = 0; i < strs[0].length(); ++i) {
        for (int j = 1; j < strs.size(); ++j) {
            if (strs[0][i] != strs[j][i])
                return ans;
            if (j == strs.size() - 1)
                ans += strs[0][i];
        }
    }
    return ans;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string a;
    vector<string> input;
    for (int i = 0; i < 2; ++i) {
        cin >> a;
        input.push_back(a);
    }
    cout << longestCommonPrefix(input) << endl;
    return 0;
}

// 其他解法
// int which_longer(string a, string b)
// {
//     if (a.length() > b.length())
//         return b.length();
//     else
//         return a.length();
// }

// string longestCommonPrefix(vector<string> &strs)
// {
//     int lng;
//     if (strs.size() < 2) // vector內只有一個或沒有string，直接回傳
//         return strs[0];
//     lng = which_longer(strs[0], strs[1]); // 比較長度，回傳比較短的
//     strs[0].erase(lng);                   // 修剪strs[0]長度至少<=比較對象
//     for (int i = 0; i < lng; ++i)         // 初始化strs[0]
//         if (strs[0][i] != strs[1][i])
//         {
//             strs[0].erase(i);
//             break;
//         }
//     for (int i = 2; i < strs.size(); ++i) // ans從strs[2]開始比較
//     {
//         lng = which_longer(strs[0], strs[i]); // 比較長度，回傳比較短的
//         strs[0].erase(lng);                   // 修剪strs[0]長度至少<=比較對象
//         for (int j = 0; j < lng; ++j)
//             if (strs[0][j] != strs[i][j])
//             {
//                 strs[0].erase(j);
//                 break;
//             }
//     }
//     return strs[0];
// }