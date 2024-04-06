#include <algorithm>
#include <iostream>

using namespace std;

// // 用temp儲放的寫法
// double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
//     vector<int> temp;
//     int n = nums1.size() + nums2.size(), nums1_index = 0, nums2_index = 0;
//     float ans;

//     if (nums1.size() == 0) {
//         if (n % 2 == 0) {
//             return float(nums2[(n + 1) / 2] + nums2[(n + 1) / 2 - 1]) / 2;
//         } else {
//             return float(nums2[(n + 1) / 2 - 1]);
//         }
//     } else if (nums2.size() == 0) {
//         if (n % 2 == 0) {
//             return float(nums1[(n + 1) / 2] + nums1[(n + 1) / 2 - 1]) / 2;
//         } else {
//             return float(nums1[(n + 1) / 2 - 1]);
//         }
//     }

//     for (int i = 0; i < (n + 1) / 2 + 1; ++i) {
//         if (nums1_index == nums1.size()) {
//             for (int j = 0; j < ((n + 1) / 2 + 1) - i; ++j) {
//                 temp.push_back(nums2[nums2_index]);
//                 ++nums2_index;
//             }
//             break;
//         }
//         if (nums2_index == nums2.size()) {
//             for (int j = 0; j < ((n + 1) / 2 + 1) - i; ++j) {
//                 temp.push_back(nums1[nums1_index]);
//                 ++nums1_index;
//             }
//             break;
//         }
//         if (nums1[nums1_index] < nums2[nums2_index]) {
//             temp.push_back(nums1[nums1_index]);
//             ++nums1_index;
//         } else {
//             temp.push_back(nums2[nums2_index]);
//             ++nums2_index;
//         }
//     }

//     if (n % 2 == 0) {
//         ans = float(temp[temp.size() - 1] + temp[temp.size() - 2]) / 2;
//     } else {
//         ans = float(temp[temp.size() - 2]);
//     }
//     return ans;
// }

// 全用判斷式的寫法，空間表現好
double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    int n = nums1.size() + nums2.size(), nums1_index = 0, nums2_index = 0;

    if (nums1.size() == 0) {
        if (n % 2 == 0) {
            return float(nums2[(n + 1) / 2] + nums2[(n + 1) / 2 - 1]) / 2;
        } else {
            return float(nums2[(n + 1) / 2 - 1]);
        }
    } else if (nums2.size() == 0) {
        if (n % 2 == 0) {
            return float(nums1[(n + 1) / 2] + nums1[(n + 1) / 2 - 1]) / 2;
        } else {
            return float(nums1[(n + 1) / 2 - 1]);
        }
    }

    for (int i = 0; i < (n + 1) / 2; ++i) {
        if (nums1_index == nums1.size()) {
            if (n % 2 == 0) {
                return float(nums2[(n + 1) / 2 - nums1_index - 1] +
                             nums2[(n + 1) / 2 - nums1_index]) /
                       2;
            } else {
                return float(nums2[(n + 1) / 2 - nums1_index - 1]);
            }
        }
        if (nums2_index == nums2.size()) {
            if (n % 2 == 0) {
                return float(nums1[(n + 1) / 2 - nums2_index - 1] +
                             nums1[(n + 1) / 2 - nums2_index]) /
                       2;
            } else {
                return float(nums1[(n + 1) / 2 - nums2_index - 1]);
            }
        }
        if (nums1[nums1_index] < nums2[nums2_index]) {
            ++nums1_index;
        } else {
            ++nums2_index;
        }
    }
    if ((n + 1) / 2 == (nums1_index + nums2_index)) {
        if (nums1_index == nums1.size()) {
            if (n % 2 == 0) {
                return float(nums1[nums1_index - 1] + nums2[nums2_index]) / 2;
            } else {
                return float(nums1[nums1_index - 1]);
            }
        } else if (nums2_index == nums2.size()) {
            if (n % 2 == 0) {
                return float(nums2[nums2_index - 1] + nums1[nums1_index]) / 2;
            } else {
                return float(nums2[nums2_index - 1]);
            }
        }
    }
    float ans = 0;
    if (n % 2 == 0) {
        if (nums1_index == 0) {
            ans += nums2[nums2_index - 1];
        } else if (nums2_index == 0) {
            ans += nums1[nums1_index - 1];
        } else if (nums1[nums1_index - 1] > nums2[nums2_index - 1]) {
            ans += nums1[nums1_index - 1];
        } else {
            ans += nums2[nums2_index - 1];
        }
        if (nums1[nums1_index] < nums2[nums2_index]) {
            ans += nums1[nums1_index];
            ans /= 2;
        } else {
            ans += nums2[nums2_index];
            ans /= 2;
        }
    } else {
        if (nums1_index == 0) {
            ans += nums2[nums2_index - 1];
        } else if (nums2_index == 0) {
            ans += nums1[nums1_index - 1];
        } else if (nums1[nums1_index - 1] > nums2[nums2_index - 1]) {
            ans += nums1[nums1_index - 1];
        } else {
            ans += nums2[nums2_index - 1];
        }
    }
    return ans;
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
int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    vector<int> input1 = {3, 5, 6}, input2 = {2, 5, 7};
    cout << "ans= " << findMedianSortedArrays(input1, input2) << endl;
    return 0;
}