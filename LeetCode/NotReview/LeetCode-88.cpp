#include <iostream>
#include <vector>
using namespace std;

// leetcode用不到，給main()用的
void printAns(vector<int> ans) {
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    vector<int> ans;
    int len = m + n;
    if (m == 0) {
        nums1.erase(nums1.begin(), nums1.end());
        for (int i = 0; i < n; ++i) {
            nums1.push_back(nums2[i]);
        }
        return;
    } else if (n == 0) {
        nums1.erase(nums1.begin() + m, nums1.end());
        return;
    }
    int index_i = 0;
    while (true) {
        if (index_i == m) {
            nums1.erase(nums1.begin() + m, nums1.end());
            for (int i = 0; i < n; ++i) {
                nums1.push_back(nums2[i]);
            }
            break;
        } else if (n == 0) {
            nums1.erase(nums1.begin() + len, nums1.end());
            break;
        }
        if (nums1[index_i] > nums2[0]) {
            nums1.insert(nums1.begin() + index_i, nums2[0]);
            nums2.erase(nums2.begin());
            ++m;
            --n;
        } else {
            ++index_i;
            continue;
        }
    }
}

int main() {
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    int m, n;
    while (cin >> m >> n) {
        vector<int> nums1, nums2;
        for (int i = 0; i < m; ++i) {
            int input;
            cin >> input;
            nums1.push_back(input);
        }
        for (int i = 0; i < n; ++i) {
            int input;
            cin >> input;
            nums2.push_back(input);
        }
        // cout << "nums1: ";
        // printAns(nums1);
        // cout << "nums2: ";
        // printAns(nums2);
        // cout << endl;
        merge(nums1, m, nums2, n);
    }
    return 0;
}
