#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

void addNewVector(vector<vector<int>> &ans, vector<int> nums, int index1, int index2, int index3) {
    vector<int> temp;
    temp.push_back(nums[index1]);
    temp.push_back(nums[index2]);
    temp.push_back(nums[index3]);
    ans.push_back(temp);
}

vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> ans;
    map<int, int> nums_map;
    map<int, map<int, bool>> check_repeat;
    int len = nums.size();
    bool firstIn = false;
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
        int abSum = 0 - nums[i];
        int check = false;
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        // cout << "hi1=" << i << '\n';
        for (int j = 0; j < nums.size(); ++j) {
            int index3 = nums_map[abSum - nums[j]] - 1;
            // cout << "hi2=" << j << "index3=" << index3 << '\n';
            if (i == j || i == index3 || j == index3 || (firstIn && (j > 0 && nums[j] == nums[j - 1]))) {
                // cout << "&&&i=" << i << ", j=" << j << ", index3=" << index3 << '\n';
                if (check) {
                    // cout << "***i=" << i << ", j=" << j << ", index3=" << index3 << '\n';
                    check_repeat[i][j] = true;
                    check_repeat[j][index3] = true;
                }
                continue;
            }
            // cout << "hi3=" << j << '\n';
            if (index3 >= 0) {
                if (!(check_repeat[i][j] || check_repeat[j][i]) && !(check_repeat[i][index3] || check_repeat[index3][i]) &&
                    !(check_repeat[j][index3] || check_repeat[index3][j])) {
                    addNewVector(ans, nums, i, j, index3);
                    // cout << "*******IN*******" << '\n';
                    // cout << "i=" << i << ", j=" << j << ", index3=" << index3 << '\n';
                    // cout << "*******IN*******" << '\n';
                    check_repeat[i][j] = true;
                    check_repeat[i][index3] = true;
                    check_repeat[j][index3] = true;
                    check = true;
                    // 01 10 04 40 14 41
                    // 03 30 02 20 32 23
                } else {
                    check = false;
                }
            }
            firstIn = true;
        }
    }
    return ans;
}

int main() {
    //-1, -4, 0, 1, 2, 2, 2, -1, -4, 3
    vector<int> input = {-2, 0, 0, 2, 2};
    vector<vector<int>> ans = threeSum(input);
    for (const auto &i : ans) {
        for (const auto &j : i) {
            cout << j << " ";
        }
        cout << ", ";
    }
    return 0;
}