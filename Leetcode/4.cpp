#include <iostream>

using namespace std;

// 全用判斷式的寫法，空間表現好
double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int mid = (nums1.size() + nums2.size() + 1) / 2, nums1_index = 0, nums2_index = 0;
    float ans1 = 0, ans2 = 0;

    for (int i = 0; i < mid + 1; ++i) {
        if (nums1_index == nums1.size() && nums2_index < nums2.size()) {
            ++nums2_index;
        } else if (nums2_index == nums2.size() && nums1_index < nums1.size()) {
            ++nums1_index;
        } else if (nums1_index < nums1.size() && nums1[nums1_index] < nums2[nums2_index]) {
            // nums1_index < nums1.size()這個要先判斷，不然遇到nums1={},nums2={1}這種情況，nums1為空指標，不能拿來跟nums2[i](int型態)比較
            ++nums1_index;
        } else {
            ++nums2_index;
        }
        if (i == mid - 1) {
            if (nums1_index == 0) {
                ans1 = nums2[nums2_index - 1];
            } else if (nums2_index == 0) {
                ans1 = nums1[nums1_index - 1];
            } else {
                ans1 = max(nums1[nums1_index - 1], nums2[nums2_index - 1]);
            }
        }
        if (i == mid && (nums1.size() + nums2.size()) % 2 == 0) {
            if (nums1_index == 0) {
                ans2 = nums2[nums2_index - 1];
            } else if (nums2_index == 0) {
                ans2 = nums1[nums1_index - 1];
            } else {
                ans2 = max(nums1[nums1_index - 1], nums2[nums2_index - 1]);
            }
            return (ans1 + ans2) / 2;
        }
    }

    return ans1;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    vector<int> input1 = {}, input2 = {1};
    cout << findMedianSortedArrays(input1, input2) << endl;
    return 0;
}

// 簡潔寫法，但時間空間都很差
//  void addTotemp(vector<int> &temp, vector<int> nums) {
//      for (int i = 0; i < nums.size(); ++i) {
//          temp.push_back(nums[i]);
//      }
//  }
//  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
//      vector<int> temp;
//      int len = nums1.size() + nums2.size();
//      addTotemp(temp, nums1);
//      addTotemp(temp, nums2);
//      sort(temp.begin(), temp.end());
//      if (len % 2 == 0) {
//          return float(temp[(len + 1) / 2 - 1] + temp[(len + 1) / 2]) / 2;
//      } else {
//          return float(temp[(len + 1) / 2 - 1]);
//      }
//  }