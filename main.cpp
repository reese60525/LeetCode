#include <algorithm>
#include <iostream>
#include <map>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

<<<<<<< HEAD
int main() {
    int sum = 0, value = 0;
    // read until end-of-file, calculating a running total of all values read
    while (std::cin >> value)
        sum += value; // equivalent to sum = sum + value
    std::cout << "Sum is: " << sum << std::endl;
=======
vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> ans;
    map<int, int> nums_map;

    // sort
    sort(nums.begin(), nums.end());

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
>>>>>>> 61a10cc8a17a134baa21322e74ffd4bf294afa1f
    return 0;
}