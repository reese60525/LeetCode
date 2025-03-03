/*
 * 題目： https://leetcode.com/problems/multiply-strings/description/
 *
 * 題目解釋：
 * 給兩個字串，字串內容為 1 ~ 200 bits 的自然數 (n >= 0)，求兩大數相乘的結果。
 *
 * 思路：
 * 模擬乘法的直式運算，將每個 bit 的運算結果存到 array 中，最後再轉為 string 輸出。
 * array 大小為 num1.size() + num2.size()，因為兩數相乘最大 bits 數為兩數 bit
 * 數的合，e.g. 9999 * 999，最多為 4 + 3 = 7 bits。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 方法 1：先將 stirng 轉成 int array 來處理乘法，再將結果轉為 string
class Solution {
  public:
    std::string multiply(std::string num1, std::string num2) {
        // 例外處理
        if (num1 == "0" || num2 == "0") {
            return "0";
        }

        std::vector<int> temp(num1.size() + num2.size(), 0);
        for (int i = num1.size() - 1; i >= 0; --i) {
            for (int j = num2.size() - 1; j >= 0; --j) {
                // 從 num1.size() + num2.size() - 1 開始存
                temp[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
                // temp[i + j] += temp[i + j + 1] / 10;
                // temp[i + j + 1] %= 10;
            }
        }

        // 等到全部 bit 都相加後再進行進位處理，可以省下很多除法和模算的時間
        for (int i = num1.size() + num2.size() - 1; i > 0; --i) {
            if (temp[i] >= 10) {
                temp[i - 1] += temp[i] / 10;
                temp[i] %= 10;
            }
        }

        // 將 array 轉為 string
        std::string res;
        for (int i = 0; i < num1.size() + num2.size(); ++i) {
            // 避免開頭為 0 的情況
            if (!res.empty() || temp[i] != 0) {
                res.push_back(temp[i] + '0');
            }
        }

        return res;
    }
};

// // 方法 2：直接用 string 來處理乘法
// class Solution {
//   public:
//     std::string multiply(std::string num1, std::string num2) {
//         // 例外處理
//         if (num1 == "0" || num2 == "0") {
//             return "0";
//         }

//         std::string res(num1.size() + num2.size(), '0');
//         for (int i = num1.size() - 1; i >= 0; --i) {
//             for (int j = num2.size() - 1; j >= 0; --j) {
//                 // 從 num1.size() + num2.size() - 1 開始存
//                 int sum = (res[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0');
//                 res[i + j + 1] = sum % 10 + '0';
//                 // out of integer range 也沒關係
//                 // 因為等等處理 res[i + j] 時，sum 會先將其 - '0'，這時得到的值仍是正確的
//                 res[i + j] += sum / 10;
//             }
//         }

//         // 去除開頭的 0
//         for (int i = 0; i < num1.size() + num2.size(); ++i) {
//             if (res[i] != '0') {
//                 return res.substr(i, num1.size() + num2.size() - i);
//             }
//         }

//         return "";
//     }
// };

int main() {

    return 0;
}