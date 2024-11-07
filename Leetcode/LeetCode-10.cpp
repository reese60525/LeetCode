/*
 * 題目：https://leetcode.com/problems/regular-expression-matching/description/
 *
 * 題目解釋：
 * 給兩組string s1和s2，s2為正規表達式，求s2是否能滿足s1。s1和s2大小不為0，s1只有小寫英文字母，s2多了'*'和'.'。
 * '.'能當作任何字母，'*'則表示在其前面的字元有0~n個。
 * e.g. s1 = "abcd" s2 = ".*"，s2表示「有0~n個'.'」，因此這個範例的s2能滿足s1，return true。
 * s1 = "abcd" s2 = ".*k"，s2表示「有0~n個'.'加上1個k」，因此這個範例的s2不能滿足s1，return false。
 * s1 = "abcd" s2 = ".*d"，s2表示「有0~n個'.'加上1個d」，因此這個範例的s2能滿足s1，return true。
 *
 * 思路：
 * 題目解說：
 * 1. https://reurl.cc/dyZLM2
 * 2. https://reurl.cc/0dNbob
 *
 * 建立dp表，由小段問題開始填表，並觀察dp之間的轉換關係，建立dp狀態轉移公式。
 * dp[i][j]的值表示「 s的前i個字元組成的字串 」能否被「 p的前j個字元組成的字串 」所滿足，
 * e.g. s = "mississippi"、p = "mis*i.*p*i"、dp[5][7] = true，表示"missi"能被"mis*i.*"滿足。
 * dp表的大小為(m+1) x (n+1)，雖然測資給的s和p的大小都大於0，但是要建立「完整」的dp表就需要額外考慮
 * s = ""或是p = ""的情況。
 *
 * 假設現在有s="aab"，p="c*a*b"，dp表如下，i為row，j為column，'-'表示為空string
 *    - c * a * b
 * -: 1 0 1 0 1 0
 * a: 0 0 0 1 1 0
 * a: 0 0 0 0 1 0
 * b: 0 0 0 0 0 1
 * 當i=0、j=0時，dp[i][j] = true，s = ""、p = ""，p能滿足s
 * 當i=0、j=1時，dp[i][j] = false，s = ""、p = "c"，p不能滿足s
 * 當i=0、j=2時，dp[i][j] = true，s = ""、p = "c*"，p能滿足s
 * 當i=1、j=0時，dp[i][j] = false，s = "a"、p = ""，p不能滿足s
 * 當i=2、j=0時，dp[i][j] = false，s = "aa"、p = ""，p不能滿足s
 *
 * i = 0時s = ""，而此時當p = ""時p就能滿足s，所以不能跳過i = 0的情況，得從i = 0開始
 * j = 0時p = ""，除了dp[0][0]之外，其餘的dp[0][j]都為false，所以j可以跳過j = 0的情況，從j = 1開始
 *
 * 由以上幾個範例可得知i = 0 時 s = ""，j = 0 時 p = ""，因此s和p是從i = 1、j = 1才開始有字元
 * 以上面的第三個例子來說明：i = 0、j = 2時，dp[i][j] = true，s = ""，p = "c*"，由此得知s正確的
 * index為i - 1 = -1，index = -1 表示 s = ""，而p正確的index為 j - 1 = 1，p = "c*"，
 * 因此當要使用到s和p的值時，要將i和j減1才能得到正確的值。
 *
 * 觀察dp之間的轉換關係，在雙迴圈中建立dp狀態轉移公式：
 *
 * 當p[j - 1] = '*'時，有三種情況可以判斷當前dp[i][j]是否為true
 * 1. dp[i][j - 2] = true時，表示'*'前面的字元出現0次。
 * dp[i][j]相比dp[i][j - 2]，其p多了"?*"，而'?'可以是任何英文字母或是'.''*'能表示0 ~ n個'?'，
 * 當dp[i][j - 2] = true，讓'?'為0個則 "?*" = ""，此時dp[i][j - 2] = dp[i][j] =true。
 *
 * 2. dp[i - 1][j] = true時，表示'*'前面的字元至少出現一次，i > 0用以保證邊界條件。
 * dp[i][j]相比dp[i - 1][j]其s多了個'?'(s[i - 1]) ，而想要讓dp[i - 1][j] = dp[i][j] = true，
 * 則s[i - 1]要和p[j - 2]相同，因為p[j - 1]是'*'可以隨意調整其前面的字元(p[j - 2])的數量，
 * 又或者s[i - 1]要和'.'相同，因為'.'可以當作任何字母使用。
 *
 * 當p[j - 1] != '*'時，有一種情況可以判斷當前dp[i][j]是否為true
 * 1. dp[i - 1][j - 1] = true時，只需考慮當前字元'?'是否匹配，i > 0用以保證邊界條件。
 * dp[i][j]相比dp[i - 1][j - 1]其s多了個'?'、p多了'?'，要讓dp[i - 1][j - 1] =dp[i][j] = true，
 * 則s[i - 1]要和p[j - 1]相同，又或者p[j - 1]要和'.'相同，因為'.'可以當作任何字母使用。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    bool isMatch(std::string s, std::string p) {
        int m = s.size(), n = p.size();
        bool dp[m + 1][n + 1]; // 建立dp表

        memset(dp, false, sizeof(dp)); // 初始化dp表為false
        dp[0][0] = true;               // dp[0][0]為true，因為當s和p都為空string時，s2能滿足s1

        for (int i = 0; i <= m; ++i) {     // i從0開始
            for (int j = 1; j <= n; ++j) { // j從1開始
                // 將p[j]的情況分為兩種，一種是p[j]為'*'，用來判斷'*'的字元出現幾次，
                // 另一種則p[j]不是'*'，僅需考慮當前字元是否匹配。
                // 由於'*'前必須有字元，因此當j >= 2才可以進入這個if判斷
                // e.g. j = 2時，p[2 - 1] = p[1]，此時才有可能p[1] = '*'。
                // 因此底下的dp[i][j - 2]不用為j添加邊界條件的判斷。
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2] || (i > 0 && dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
                }
                else {
                    dp[i][j] = i > 0 && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                }
            }
        }

        // // test，用於印出完整的dp表
        // std::cout << "     ";
        // for (int i = 0; i < n; ++i) {
        //     std::cout << p[i] << ' ';
        // }
        // std::cout << '\n';
        // for (int i = 0; i <= m; ++i) {
        //     if (i == 0) {
        //         std::cout << "-: ";
        //     }
        //     else {
        //         std::cout << s[i - 1] << ": ";
        //     }

        //     for (int j = 0; j <= n; ++j) {
        //         std::cout << dp[i][j] << ' ';
        //     }
        //     std::cout << '\n';
        // }
        // std::cout << '\n';

        return dp[m][n];
    }
};

int main() {

    return 0;
}