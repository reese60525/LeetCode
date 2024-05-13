#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 參考別人的解法:two pointer
std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
    std::vector<std::vector<int>> ans;
    int l, r, n = nums.size();
    // 排序
    sort(nums.begin(), nums.end());

    for (int i = 0; i < n; ++i) {
        l = i + 1; // l從左開始
        r = n - 1; // r從右開始
        while (l < r) {
            int target = nums[i] + nums[l] + nums[r];
            if (target == 0) {
                ans.push_back(std::vector({nums[i], nums[l], nums[r]}));
                while (l < r && nums[l] == nums[l + 1]) { // 重複的跳過
                    ++l;
                }
                while (l < r && nums[r] == nums[r - 1]) { // 重複的跳過
                    --r;
                }
                ++l;
                --r;
            }
            else if (target > 0) {
                --r;
            }
            else {
                ++l;
            }
        }
        while (i + 1 < n && nums[i] == nums[i + 1]) { // 重複的跳過
            ++i;
        }
    }
    return ans;
}
int main() {
    //-1, -4, 0, 1, 2, 2, 2, -1, -4, 3
    std::vector<int> input = {-1, 0, 1, 2, -1, -4};
    std::vector<std::vector<int>> ans = threeSum(input);
    for (const auto &i : ans) {
        for (const auto &j : i) {
            std::cout << j << " ";
        }
        std::cout << ", ";
    }
    return 0;
}

// // 自己想的解法
// #include <algorithm>
// #include <iostream>
// #include <unordered_map>

// using namespace std;

// static const auto io_sync_off = []() {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     return nullptr;
// }();

// vector<vector<int>> threeSum(vector<int> &nums) {
//     vector<vector<int>> ans;
//     unordered_map<int, int> nums_map;

//     // sort
//     sort(nums.begin(), nums.end());

//     // 把num放進map做hash table
//     for (int i = 0; i < nums.size(); ++i) {
//         nums_map[nums[i]] = i + 1;
//     }

//     // 每輪i迴圈都會把nums[i]的所有目標組合(3sums=0)都找出來
//     // 因此j迴圈不必從0開始，因為比i小的都做過了
//     for (int i = 0; i < nums.size(); ++i) {
//         // 重複的nums[i]不要重複做
//         if (i > 0 && nums[i] == nums[i - 1]) {
//             continue;
//         }
//         for (int j = i + 1; j < nums.size(); ++j) {
//             // 第三個num的值
//             int third_num = 0 - nums[i] - nums[j];
//             // 條件1；第三個num如果比nums[j]小代表已經做過了
//             // 條件2:超出nums的範圍
//             // 條件3:重複的nums[j]別重做，並且j!=i
//             if (third_num < nums[j] || third_num > nums[nums.size() - 1] || (j != i + 1 && nums[j] == nums[j -
//             1])) {
//                 continue;
//             }
//             int index3 = nums_map[third_num] - 1;
//             // 第三個num的index = 第二個num的index則跳過
//             if (index3 == j) {
//                 continue;
//             }
//             // index3>=代表在hash table中有這個值(third_num)
//             if (index3 >= 0) {
//                 ans.push_back(vector({nums[i], nums[j], nums[index3]}));
//             }
//         }
//     }
//     return ans;
// }

// int main() {
//     //-1, -4, 0, 1, 2, 2, 2, -1, -4, 3
//     vector<int> input = {-1, 0, 1, 2, -1, -4};
//     vector<vector<int>> ans = threeSum(input);
//     for (const auto &i : ans) {
//         for (const auto &j : i) {
//             cout << j << " ";
//         }
//         cout << ", ";
//     }
//     return 0;
// }