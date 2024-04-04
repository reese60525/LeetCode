#include <iostream>
using namespace std;

int removeDuplicates(vector<int> &nums) {
    // 超慢寫法 遇到相同的就刪掉一次
    // int k = 0;
    // for (int i = 0; i < nums.size() - 1; ++i) {
    //     if (nums[i] == nums[i + 1]) {
    //         nums.erase(nums.begin() + i + 1);
    //         --i;
    //     } else {
    //         ++k;
    //     }
    // }
    // return ++k;

    // 比較快的寫法 遇到不同的就一次把相同的整段刪掉
    int k = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[k] != nums[i]) {
            nums.erase(nums.begin() + k + 1, nums.begin() + i);
            ++k;
            i = k;
        }
    }
    if (nums[k] == nums[nums.size() - 1])
        nums.erase(nums.begin() + k + 1, nums.end());
    return ++k;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
}