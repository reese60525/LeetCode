#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

void fun1(int num, map<int, int> *map_count, vector<int> *k) {
    int temp = num;
    if (temp % 2 == 0)
        *k.push_back(2);
    while (temp % 2 == 0) {
        *map_count[2]++;
        temp /= 2;
    }
    for (int i = 3; i < sqrt(num); i += 2) {
        if (temp % i == 0)
            *k.push_back(i);
        while (temp % i == 0) {
            ++*map_count[i];
            temp /= i;
        }
        if (temp == 1)
            break;
    }
    if (temp > 1) {
        ++*map_count[temp];
        *k.push_back(temp);
    }
}

int fun2(map<int, int> map_a, map<int, int> map_b, vector<int> k) {
    int GCD = 1;
    cout << "k.size()= " << k.size() << endl;
    for (int i = 0; i < k.size(); ++i) {
        int temp_a = map_a[k[i]];
        int temp_b = map_b[k[i]];
        cout << "k= " << k[i] << ", temp_a= " << temp_a << ", tmep_b= " << temp_b << endl;
        if (temp_b > 0 && temp_b > temp_a)
            GCD *= (k[i] * temp_a);
        else if (temp_b > 0 && temp_b <= temp_a)
            GCD *= (k[i] * temp_b);
        cout << "gcd= " << GCD << endl;
    }
    return GCD;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int a, b;
    while (cin >> a >> b) {
        map<int, int> map_a, map_b;
        vector<int> k;
        fun1(b, &map_b, &k);
        k.erase(k.begin(), k.end());
        fun1(a, &map_a, &k);
        cout << fun2(map_a, map_b, k) << endl;
    }
    return 0;
}