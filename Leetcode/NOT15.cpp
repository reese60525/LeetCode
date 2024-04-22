#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> ans;
    map<int, int> nums_map;

    // sort
    sort(nums.begin(), nums.end());
    // cout << "size:" << nums.size() << '\n';
    // for (auto i : nums) {
    //     cout << i << " ";
    // }
    // cout << '\n';

    for (int i = 0; i < nums.size(); ++i) {
        nums_map[nums[i]] = i + 1;
    }

    for (int i = 0; i < nums.size(); ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        for (int j = i + 1; j < nums.size(); ++j) {
            int third_num = 0 - nums[i] - nums[j];
            if (third_num < nums[j] || third_num > nums[nums.size() - 1] ||
                (j != i + 1 && nums[j] == nums[j - 1])) {
                continue;
            }
            int index3 = nums_map[third_num] - 1;
            if (index3 == j) {
                continue;
            }
            if (index3 >= 0) {
                // cout << "\nIndex3 >= 0" << "\n";
                // cout << "i=" << i << ", j=" << j << ", index3=" << index3 << '\n';
                // cout << "nums[i]=" << nums[i] << ", nums[j]=" << nums[j]
                //      << ", nums[index3]=" << nums[index3] << '\n';
                // cout << "Index3 >= 0" << "\n";
                vector<int> temp;
                temp.push_back(nums[i]);
                temp.push_back(nums[j]);
                temp.push_back(nums[index3]);
                ans.push_back(temp);
            }
        }
    }
    return ans;
}

int main() {
    //-1, -4, 0, 1, 2, 2, 2, -1, -4, 3
    vector<int> input = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> ans = threeSum(input);
    for (const auto &i : ans) {
        for (const auto &j : i) {
            cout << j << " ";
        }
        cout << ", ";
    }
    return 0;
}