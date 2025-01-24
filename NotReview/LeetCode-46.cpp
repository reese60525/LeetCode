#include <iostream>

using namespace std;

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

void recursive_ans(vector<vector<int>> &ans, vector<int> nums, vector<int> current) {
    if (nums.size() == 0) {
        ans.push_back(current);
    }
    for (int i = 0; i < nums.size(); ++i) {
        vector<int> temp1 = nums;
        vector<int> temp2 = current;
        temp2.push_back(nums[i]);
        temp1.erase(temp1.begin() + i);
        recursive_ans(ans, temp1, temp2);
    }
}

vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> ans;
    recursive_ans(ans, nums, {});
    return ans;
}

int main() {
    vector<int> input = {1, 2, 3};
    permute(input);
    return 0;
}