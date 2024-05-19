/*
 * 題目:
 * 題目解釋:
 * 思路:
 * 解法:
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    long long maximumValueSum(std::vector<int> &nums, int k, std::vector<std::vector<int>> &edges) {
        std::vector<std::vector<int>> newEdges;
        for (auto edge : edges) {
            newEdges.emplace_back(std::vector<int> {edge[1], edge[0]});
        }
        edges.insert(edges.end(), newEdges.begin(), newEdges.end());

        std::sort(edges.begin(), edges.end());

        // for (auto i : edges) {
        //     std::cout << i[0] << ", " << i[1] << '\n';
        // }

        for (auto edge : edges) {
            if (((nums[edge[0]] ^ k) + (nums[edge[1]] ^ k)) > (nums[edge[0]] + nums[edge[1]])) {
                nums[edge[0]] ^= k;
                nums[edge[1]] ^= k;
            }
        }

        long long res = 0;
        for (auto i : nums) {
            res += i;
        }
        return res;
    }
};

int main() {
    int a, b;
    while (std::cin >> a >> b) {
        std::cout << (a ^ b) << '\n';
    }
    return 0;
}