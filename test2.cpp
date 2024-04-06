#include <iostream>
using namespace std;

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    vector<char> x = {'1', '2', '3', '4', '5', '6'};
    x.erase(x.begin());
    for (int i = 0; i < x.size(); ++i) {
        cout << x[i] << " ";
    }
    return 0;
}