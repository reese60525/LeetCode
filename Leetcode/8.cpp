#include <iostream>
using namespace std;

int myAtoi(string s) {
    int is_negative = 1;
    long long ans = 0;
    bool read_nums = false, erase_headZero = true;
    for (int i = 0; i < s.length(); ++i) {
        // "abc 123" 先文字在數字要return 0
        if (s[i] != ' ' && s[i] != '+' && s[i] != '-' && (s[i] < 48 || s[i] > 57))
            break;
        if (read_nums && (s[i] < 48 || s[i] > 57)) // 讀完一組數字後跳出迴圈
            break;
        if (s[i] == '+' && (s[i + 1] < 48 || s[i + 1] > 57)) { // " + 1"正號後不是數字要return 0
            break;
        }
        if (s[i] == '-' && (s[i + 1] < 48 || s[i + 1] > 57)) { // " - 1"負號後不是數字要return 0
            break;
        }
        if (erase_headZero && (s[i] >= 49 && s[i] <= 57)) //"000123"的0都跳過
            erase_headZero = false;
        if ((s[i] >= 48 && s[i] <= 57)) { // 確認是否開始讀數字
            if (i > 0 && s[i - 1] == '-') // 確認該數是正還是負
                is_negative = -1;
            read_nums = true;
        }
        if (read_nums && !erase_headZero && (s[i] >= 48 && s[i] <= 57)) {
            ans = ans * 10 + (s[i] - '0');
            if (ans * is_negative > INT_MAX) // 超過int範圍就return 0
                return INT_MAX;
            if (ans * is_negative < INT_MIN) // 超過int範圍就return 0
                return INT_MIN;
        }
    }
    return ans * is_negative;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string input = "-12+23";
    cout << myAtoi(input) << endl;
    // while (cin >> input) {
    //     cout << myAtoi(input) << endl;
    // }
    return 0;
}