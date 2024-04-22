#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
// map<int,bool> check; 用來確認該數組是否已經print過
// 新增一組數組後，兩兩相加放入map中，並把數值改成true

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
    map<int, map<int, bool>> repeat_check;

    // sort
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); ++i) {
        nums_map[nums[i]] = i + 1;
    }

    for (int i = 0; i < nums.size(); ++i) {
        int abSum = 0 - nums[i];
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        for (int j = 0; j < nums.size(); ++j) {
            if (abSum - nums[j] < nums[0] || abSum - nums[j] > nums[nums.size() - 1]) {
                continue;
            }
            int index3 = nums_map[abSum - nums[j]] - 1;
            if (i == j || i == index3 || j == index3) {
                continue;
            }
            if (index3 >= 0) {
                if (!(repeat_check[nums[i]][nums[j]] || repeat_check[nums[i]][nums[index3]] ||
                      repeat_check[nums[j]][nums[index3]] || repeat_check[nums[j]][nums[i]] ||
                      repeat_check[nums[index3]][nums[i]] || repeat_check[nums[index3]][nums[j]])) {
                    addNewVector(ans, nums, i, j, index3);
                    repeat_check[nums[i]][nums[j]] = true;
                    repeat_check[nums[i]][nums[index3]] = true;
                    repeat_check[nums[index3]][nums[j]] = true;
                    repeat_check[nums[j]][nums[i]] = true;
                    repeat_check[nums[index3]][nums[i]] = true;
                    repeat_check[nums[j]][nums[index3]] = true;
                }
            }
        }
    }
    return ans;
}

int main() {
    //-1, -4, 0, 1, 2, 2, 2, -1, -4, 3
    vector<int> input = {-1, 0, 1, 2, -1, -4, -2, -3, 3, 0, 4};
    vector<vector<int>> ans = threeSum(input);
    for (const auto &i : ans) {
        for (const auto &j : i) {
            cout << j << " ";
        }
        cout << ", ";
    }
    return 0;
}

// Temp code
//  #include <algorithm>
//  #include <iostream>
//  #include <map>

// using namespace std;

// static const auto io_sync_off = []() {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     return nullptr;
// }();

// vector<vector<int>> threeSum(vector<int> &nums) {
//     vector<vector<int>> ans;
//     map<int, int> sum;

//     sort(nums.begin(), nums.end());
//     // cout << "size:" << nums.size() << '\n';
//     // for (auto i : nums) {
//     //     cout << i << " ";
//     // }
//     // cout << '\n';

//     for (int i = 1; i < nums.size(); ++i) {
//         sum[0 - nums[i]] = i + 1;
//     }

//     for (int i = 0; i < nums.size() - 1; ++i) {
//         if (i > 0 && nums[i] == nums[i - 1]) {
//             continue;
//         }
//         for (int j = i + 1; j < nums.size(); ++j) {
//             if (j > i + 1 && nums[j] == nums[j - 1]) {
//                 continue;
//             }
//             // cout << "i=" << i << ", j=" << j;
//             // cout << ", sum=" << sum[nums[i] + nums[j]] << '\n';
//             // cout << "mum[i]=" << nums[i] << ", mum[j]=" << nums[j] << ", map_index=" <<
//             nums[i] + nums[j]
//             //      << ", map=" << sum[nums[i] + nums[j]] << ", mum[map]=" << nums[sum[nums[i] +
//             nums[j]]] << "\n\n"; int index = sum[nums[i] + nums[j]]; if (index != 0 && index - 1
//             != i && index - 1 != j) {
//                 // cout << "***********************" << '\n';
//                 vector<int> temp;
//                 temp.push_back(nums[i]);
//                 temp.push_back(nums[j]);
//                 temp.push_back(0 - (nums[i] + nums[j]));
//                 sort(temp.begin(), temp.end());
//                 ans.push_back(temp);
//                 // if (ans.size() == 0) {
//                 //     ans.push_back(temp);
//                 // } else {
//                 //     int i;
//                 //     for (i = 0; i < ans.size(); ++i) {
//                 //         if (ans[i] == temp) {
//                 //             break;
//                 //         }
//                 //     }
//                 //     if (i == ans.size()) {
//                 //         ans.push_back(temp);
//                 //     }
//                 // }
//             }
//         }
//     }
//     if (ans.size() == 0)
//         return ans;
//     int begin = 0;
//     sort(ans.begin(), ans.end());
//     for (int i = 1; i < ans.size() - 1; ++i) {
//         if (ans[begin] != ans[i]) {
//             if ((i - 1) != begin && ans[begin] == ans[i - 1]) {
//                 ans.erase(ans.begin() + begin, ans.begin() + i - 1);
//                 i = begin + 1;
//             }
//             ++begin;
//         }
//     }
//     if (begin != ans.size() - 1) {
//         ans.erase(ans.begin() + begin, ans.end() - 1);
//     }

//     // for (int i = 0; i < ans.size() - 1; i = i) {
//     //     if (ans[i] == ans[i + 1]) {
//     //         ans.erase(ans.begin() + i);
//     //     } else {
//     //         ++i;
//     //     }
//     // }
//     return ans;
// }

// int main() {
//     //-1, -4, 0, 1, 2, 2, 2, -1, -4, 3
//     vector<int> input = {-1, -4, 0, 1, 2, 2, 2, -1, -4, 3};
//     vector<vector<int>> ans = threeSum(input);
//     for (const auto &i : ans) {
//         for (const auto &j : i) {
//             cout << j << " ";
//         }
//         cout << ", ";
//     }
//     return 0;
// }