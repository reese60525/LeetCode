#include <iostream>
#include <vector>
using namespace std;

// 比較快但空間大
string removeStars(string s) {
    vector<char> temp;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '*') {
            temp.erase(temp.end() - 1);
        } else {
            temp.push_back(s[i]);
        }
    }
    string ans = "";
    for (int i = 0; i < temp.size(); ++i) {
        ans += temp[i];
    }
    return ans;
}

// 比較慢但空間小
// string removeStars(string s) {
//     vector<string> temp;
//     temp.push_back("");
//     for (int i = 0; i < s.length(); ++i) {
//         if (s[i] == '*') {
//             temp[0].erase(temp[0].end() - 1);
//         } else {
//             temp[0].push_back(s[i]);
//         }
//     }
//     return temp[0];
// }

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string input;
    while (cin >> input) {
        cout << removeStars(input) << endl;
    }
    return 0;
}