// 解題思路:
// 因為2c = c+c ,2c+1 = c + c+1 ... 3c-1= c + 2c-1 以此類推
// 若c~2c-1之間(包含頭尾)的數目都能找到一組正自然數[x,y] :ax+by來滿足
// 則該a,b能滿足題目需求
#include <iostream>
using namespace std;

string fun(int a, int b, int c) {
    int temp[2];
    if (a > c && b > c) // c小於a和b 則為No
        return "No";

    if (a <= c) {
        temp[0] = a;
        temp[1] = b;
    } else {
        temp[0] = b;
        temp[1] = a;
    }
    for (int i = c; i <= c * 2 - 1; ++i) // c~c-1的範圍一一檢查
    {
        bool check = false;
        for (int j = 0; j <= i / temp[0]; ++j) // 0個temp[0]到temp*j <= i之最大值
        {
            if (double(i - j * temp[0]) / temp[1] == (i - j * temp[0]) / temp[1]) {
                check = true;
                break;
            }
        }
        if (!check)
            return "No";
    }

    return "Yes";
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int a, b, c;
    while (cin >> a >> b >> c)
        cout << fun(a, b, c) << endl;
    return 0;
}
