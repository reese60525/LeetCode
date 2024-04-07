#include <iostream>
using namespace std;

int male, female;

int male_count(int male, int n) {
    if (n == 0) {
        return 0;
    }
    return male_count(male += female + 1, --n);
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int n;
    while (cin >> n) {
        male = 0, female = 0;
        if (n == -1) {
            break;
        }
        cout << male_count(male, n) << " " << male_count(male, n) + female_count(0, n) + 1;
    }
    return 0;
}