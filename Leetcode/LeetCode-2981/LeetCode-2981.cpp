#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int maximumLength(std::string s) {
        int res = -1, len = 0;  // len 紀錄當前 special substring 的長度
        int freq[26][50] = {0}; // 紀錄每種字母每個 special substring 出現的次數

        for (int i = 0; i < s.size(); i++) {
            ++len;

            // 到字串末端 或是 當前字母與下一個字母不同時，代表當前 special substring 結束
            if (i == s.size() - 1 || s[i] != s[i + 1]) {
                // 由該 special substring 所能組成的 substring 也是 special substring
                // 將每種長度的 special substring 累加
                for (int j = 0; j < len; ++j) {
                    freq[s[i] - 'a'][j] += len - j;
                    // 如果該字母當前長度的 special substring 出現次數大於等於 3 則去跟 res 比較
                    if (freq[s[i] - 'a'][j] >= 3) {
                        res = std::max(res, j + 1);
                    }
                }
                len = 0;
            }
        }

        return res;
    }
};

int main() {

    return 0;
}