#include <iostream>
#include <string>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int lengthOfLastWord(std::string s) {
        int ans = 0;
        bool check = false;
        for (int i = s.length() - 1; i >= 0; --i) {
            if (check && s[i] == ' ')
                break;
            else if (!check && s[i] != ' ')
                check = true;
            if (check)
                ++ans;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    std::string s;
    while (std::cin >> s)
        std::cout << solution.lengthOfLastWord(s) << '\n';

    return 0;
}