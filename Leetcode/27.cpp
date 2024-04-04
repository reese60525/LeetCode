#include <iostream>
#include <vector>
using namespace std;

int removeElement(vector<int> &nums, int val) {
    int k = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == val) {
            nums.erase(nums.begin() + i);
            --i;
            continue;
        }
        ++k;
    }
    return k;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    vector<int> input;
    int val, len, k;
    cin >> len >> val;
    for (int i = 0; i < len; ++i) {
        int temp;
        cin >> temp;
        input.push_back(temp);
    }
    k = removeElement(input, val);
    cout << "k= " << k << endl;
    for (int i = 0; i < k; ++i) {
        cout << input[i] << " ";
    }

    return 0;
}