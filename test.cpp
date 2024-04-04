#include <iostream>
using namespace std;

double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    int index_1 = 0, index_2 = 0, n;
    float ans = 0;
    n = (nums1.size() + nums2.size() + 1) / 2;
    for (int i = 0; i < n; ++i) {
        if (index_1 == nums1.size() || index_2 == nums2.size())
            break;
        if (nums1[index_1] > nums2[index_2]) {
            ++index_2;
        } else {
            ++index_1;
        }
    }

    if (index_1 == nums1.size()) {
        if (index_1 == n) {
            ans += nums1[index_1 - 1];
        } else {
            index_2 += (n + 1) - nums1.size();
            ans += nums2[index_2 - 1];
        }
    } else if (index_2 == nums2.size()) {
        if (index_2 == n) {
            ans += nums2[index_2 - 1];
        } else {
            index_1 += (n + 1) - nums2.size();
            ans += nums1[index_1 - 1];
        }
    } else if (nums1[index_1 - 1] > nums2[index_2 - 1]) {
        ans += nums1[index_1 - 1];
    } else {
        ans += nums2[index_2 - 1];
    }

    if ((nums1.size() + nums2.size()) % 2 == 0) {
        if (index_1 == nums1.size()) {
            if (index_1 == n) {
                ans += nums2[0];
            } else {
                ans += nums2[index_2 - 2];
            }
        } else if (index_2 == nums2.size()) {
            if (index_2 == n) {
                ans += nums1[0];
            } else {
                ans += nums1[index_2 - 2];
            }
        } else if (nums1[index_1] > nums2[index_2]) {
            ans += nums2[index_2];
        } else {
            ans += nums1[index_1];
        }
        ans /= 2;
    }
    return ans;
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
}