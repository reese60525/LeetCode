#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int longestSubstring(std::string s, int k) {
        int ans = 0;

        return ans;
    }
};

int main() {
    Solution solution;
    std::string s;
    int k;
    while (std::cin >> s >> k)
        std::cout << solution.longestSubstring(s, k) << '\n';
    return 0;
}