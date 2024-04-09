#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maxArea(vector<int> &height) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int maxArea = 0, left = 0, right = height.size() - 1;
    while (left != right) {
        int nowArea = min(height[left], height[right]) * (right - left);
        maxArea = max(maxArea, nowArea);
        height[left] < height[right] ? ++left : --right;
    }
    return maxArea;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    vector<int> input = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << maxArea(input) << endl;
    return 0;
}