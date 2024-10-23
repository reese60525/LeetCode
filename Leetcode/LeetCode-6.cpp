/*
 * 題目： https://leetcode.com/problems/zigzag-conversion/description/
 *
 * 題目解釋：
 * 給一組string，假設令其以鋸齒狀呈現，回傳以橫列由上而下讀所得到的string。
 * e.g. input string = "PAYPALISHIRING"，先將其以鋸齒狀呈現，如下所示。
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * 接著再以由上而下橫行來看，會得到output string = "PAHNAPLSIIGYIR"
 *
 * 思路：
 * 使用二維陣列依照鋸齒狀上下移動儲存字元，最後再逐行輸出字元。
 * 以上面的例子來說，numRows = 3，所以會有3個row，每個row剛開始都是空string，如果當前所在的
 * row是最上面(row = 0)或最下面(row = numRows - 1)，則要改變方向(dir *= -1)。一開始row
 * 在第一層(row = 0)，因此vector[0]加上當前字元(P)，並判斷目前row是否處於邊界，是的話則要改變移
 * 動方向，然後再將row移動到下一個row(row + dir)。接著row在第二層(row = 1)，dir = 1，
 * vector[1]加上當前字元(A)，然後row移到第三層(row = 2)，vector[2]加上當前字元(Y)，此時row在邊界，
 * 因此dir *= -1(dir = -1)，row移動到第二層(row(2) + dir(-1))，以此類推，直到遍歷整個string，
 * 最後vector[1] = PAHN、vector[2] = APLSIIG、vector[1] = YIR，將所有vector[i]串接成string
 * 即可得到答案。
 */
#include <iostream>
#include <string>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::string convert(std::string s, int numRows) {
        if (numRows == 1) {
            return s;
        }

        int cur_row = 0, dir = -1; // 初始row為第一層，dir為移動方向
        std::vector<std::string> res(numRows);

        for (int i = 0; i < s.length(); ++i) {
            res[cur_row] += s[i];

            // 判斷目前row是否處於邊界，是的話則要改變移動方向
            if (cur_row == 0 || cur_row == numRows - 1) {
                dir *= -1;
            }
            cur_row += dir; // 移動至下一層row
        }

        // 將所有res[i]串接成到res[0]
        for (int i = 1; i < numRows; ++i) {
            res[0] += res[i];
        }

        return res[0];
    }
};

int main() {

    return 0;
}
// num = 1
// aaaaaa

// num =2
// aaaa
// aaaa

// num = 3
// a a a
// aaaaa
// a a a

// num = 4
// a  a  a  a
// a aa aa aa
// aa aa aa a
// a  a  a  a

// num = 5
// a   a   a
// a  aa  aa
// a a a a a
// aa  aa  a
// a   a   a

// num = 8
//  a      a      a
//  a     aa     aa
//  a    a a    a a
//  a   a  a   a  a
//  a  a   a  a   a
//  a a    a a    a
//  aa     aa     a
//  a      a      a