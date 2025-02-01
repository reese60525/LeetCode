#include <iostream>
using namespace std;

int removeDuplicates(vector<int> &nums) {
    int now_num = nums[0], num_count = 0, index_begin = -1;
    for (int i = 0; i < nums.size(); ++i) {
        if (now_num != nums[i]) {
            now_num = nums[i];
            num_count = 1;
            if (index_begin != -1) {
                nums.erase(nums.begin() + index_begin, nums.begin() + i);
                i = index_begin;
                index_begin = -1;
            }
        } else {
            ++num_count;
        }
        if (num_count > 2 && index_begin == -1) {
            index_begin = i;
        }
    }
    if (index_begin != -1) {
        nums.erase(nums.begin() + index_begin, nums.end());
    }
    return nums.size();
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
}