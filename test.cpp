#include <iostream>
#include <vector>

using namespace std;

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    vector<int> ans = {1, 2, 3, 4, 5, 0, 0, 0};
    ans.erase(ans.begin() + 6, ans.end());
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}