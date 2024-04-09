#include <algorithm>
#include <iostream>

using namespace std;

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> ans;
    bool jump[2] = {false, false};
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size() - 2; ++i) {
        if (nums[i] > 0) {
            break;
        }
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        for (int j = i + 1; j < nums.size() - 1; ++j) {
            if (nums[i] + nums[j] > 0) {
                break;
            }
            if (jump[0] && j > 1 & nums[j] == nums[j - 1]) {
                continue;
            }
            for (int k = nums.size() - 1; k > j; --k) {
                if (jump[1] && k < nums.size() - 1 & nums[k] == nums[k + 1]) {
                    continue;
                }
                if ((nums[i] + nums[j] + nums[k]) == 0) {
                    vector<int> temp;
                    temp.push_back(nums[i]);
                    temp.push_back(nums[j]);
                    temp.push_back(nums[k]);
                    ans.push_back(temp);
                    break;
                }
                jump[1] = true;
            }
            jump[0] = true;
            jump[1] = false;
        }
        jump[0] = false;
    }

    return ans;
}

int main() {
    vector<int> input = {-1, -4, 0, 1, 2, 2, 2, -1, -4, 3};
    vector<vector<int>> ans = threeSum(input);
    for (const auto &i : ans) {
        for (const auto &j : i) {
            cout << j << " ";
        }
        cout << ", ";
    }
    return 0;
}