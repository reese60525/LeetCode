#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int maximumLength(std::string s) {
        int res = -1, count = 0;
        int freq[26][50] = {0};

        for (int i = 0; i < s.size(); i++) {
            ++count;

            if (i == s.size() - 1 || s[i] != s[i + 1]) {
                for (int j = 0; j < count; ++j) {
                    freq[s[i] - 'a'][j] += count - j;
                    if (freq[s[i] - 'a'][j] >= 3) {
                        res = std::max(res, j + 1);
                    }
                }
                count = 0;
            }
        }

        return res;
    }
};

int main() {

    return 0;
}