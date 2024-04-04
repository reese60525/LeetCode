#include <iostream>
#include <vector>

using namespace std;

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    vector<int> ans = {1, 2, 3, 4, 5, 6, 7, 8};
    ans.erase(ans.begin() + 1, ans.begin() + 1);
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}