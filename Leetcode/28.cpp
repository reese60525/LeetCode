#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// KMP Algorithm
class Solution {
  public:
    // abcabe
    // i = 0, sub = a
    // i = 1, sub = ab, (a,b)
    // i = 2, sub = abc, (ab,bc)、(a,c)
    // i = 3, sub = abca, (abc,bca)、(ab,ca)、(a,a) => next[3] = 1;
    // i = 4, sub = abcab, (abca,bcab)、(abc,cab)、(ab,ab) => next[4] = 2;
    int *get_next(std::string needle) {
        int *next = new int[needle.length() - 1]; // needle本身不需要建表，因為當haystack有substring和needle一樣就會直接return index了。
        memset(next, 0, (needle.length() - 1) * sizeof(*next)); // size記得-1
        for (int i = 0; i < needle.length() - 1; ++i) {
            std::string sub = needle.substr(0, i + 1);
            for (int j = sub.length() - 1; j >= 1; --j) {
                if (sub.substr(0, j) == sub.substr(sub.length() - j, j)) {
                    next[i] = j;
                    break; // 找到最長的就break，以免後續短的取代掉長的。
                }
            }
        }
        return next;
    }

    int strStr(std::string haystack, std::string needle) {
        int *next = get_next(needle); // next[i]代表string有i+1個字相同
        int len = haystack.length() - needle.length(), round = needle.length();
        for (int i = 0; i <= len;) {
            for (int j = 0; j < round; ++j) {
                if (haystack[i + j] != needle[j]) {
                    if (j == 0)
                        ++i;
                    else
                        i += (j - next[j - 1]); // index = j時有不同的字母，代表字串前面有j個相同，帶入next要用j-1，在next表示代表有j個相同
                    break; // j-next[j-1]，代表j個相同-LFS = 要位移的數目。
                }
                if (j == round - 1)
                    return i;
            }
        }
        return -1;
    }
};

int main() {
    Solution solution;
    std::string a, b;
    while (std::cin >> a >> b)
        std::cout << solution.strStr(a, b) << '\n';
    return 0;
}