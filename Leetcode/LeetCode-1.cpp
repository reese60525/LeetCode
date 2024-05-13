#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> a;
    vector<int> ans;

    for (int i = 0; i < nums.size(); ++i) {
        if (a.find(target - nums[i]) != a.end()) {
            ans.push_back(a[target - nums[i]]);
            ans.push_back(i);
            return ans;
        }
        a[nums[i]] = i;
    }
    return ans;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    vector<int> input = {0, 4, 3, 0};
    int target = 0;
    vector<int> ans = twoSum(input, target);
    cout << "[" << ans[0] << "," << ans[1] << "]" << endl;
}