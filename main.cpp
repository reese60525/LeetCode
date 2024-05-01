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
        int *next = new int[needle.length() - 1];
        memset(next, 0, needle.length() * sizeof(*next));
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
        int *next = get_next(needle);
        int len = haystack.length() - needle.length(), round = needle.length();
        for (int i = 0; i <= len;) {
            for (int j = 0; j < round; ++j) {
                if (haystack[i + j] != needle[j]) {
                    if (j == 0)
                        ++i;
                    else
                        i += (j - next[j - 1]);
                    break;
                }
                if (j == round - 1)
                    return i;
            }
        }
        return -1;
    }
};