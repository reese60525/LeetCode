#include <iostream>
using namespace std;

long long male_count = 0;
long long female_count = 0;

void fun(long long male, long long female, int n) {
    if (n <= 0) {
        return;
    }
    long long male_temp = male;
    ++male;
    male += female;
    female = male_temp;
    male_count = male;
    female_count = female;
    fun(male, female, --n);
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int n;
    while (cin >> n) {
        male_count = 0;
        female_count = 0;
        if (n == -1) {
            break;
        }
        fun(0, 0, n);
        cout << male_count << " " << female_count + male_count + 1 << endl;
    }
    return 0;
}