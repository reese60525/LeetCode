/*
 * 題目： https://leetcode.com/problems/divide-two-integers/description/
 *
 * 題目解釋：
 * 給兩個整數x, y，求x除以y的無條件捨去商。
 * 條件1:不能使用乘法、除法、模運算。
 * 條件2:假設該程式正在一個只能處理儲存"32位元有符號整數範圍內的整數"的環境。
 *
 * 思路：
 * 先判斷極端情況，當divisor為INT_MIN時，如果divident也是INT_MIN，retrun 1否則return 0。
 * 接著判斷兩數相除是正數還是負數，輸出結果時會用到。將兩數都轉成正數，如果有INT_MIN則轉正數會造
 * 成溢出，divisor在極端條件有先處理該情況，而dividend可以將INT_MIN轉成INT_MAX，之後做完商
 * 運算後，剩下的餘數+1如果剛好能被整除，則將結果依照正負數+1或-1。需要注意的是有個極端情況要考慮，
 * 例如：dividend = INT_MIN, divisor = -1，兩者轉正會變成dividend = INT_MAX, divisor = 1，
 * 此時計算完後res會是INT_MAX，如果將res + 1會變成INT_MAX + 1造成溢出，因此需要額外判斷res
 * 是小於INT_MAX。在商運算中是模擬長除法來實作，有疑問就自己去將binary用長除法做一遍就知道了。

 * 有大神的方法，思路很帥，我是選擇將dividend和divisor都轉為"正數"，但是這樣dividend如果是INT_MIN
 * 會導致轉正數後溢出，因此大神的做法是將兩數都轉成"負數"，由於INT_MAX轉成負數是INT_MIN-1因此不會溢出，
 * 而在長除法中的判斷則剛好跟正數的相反，這種方式省去而外處理dividend是INT_MIN的極端情況。
 */
#include <climits>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 我的方式
class Solution {
  public:
    int divide(int dividend, int divisor) {
        // 處理極端情況
        if (divisor == INT_MIN) {
            return dividend == INT_MIN ? 1 : 0;
        }

        // 當兩個數的符號位不同（即正負不同）時，dividend ^ divisor的最高有效位（MSB）會是1(表示負數)
        bool is_negative = (dividend ^ divisor) < 0;
        bool is_dividend_int_min = dividend == INT_MIN;

        // 將兩個數都轉換成正數，如果dividend是INT_MIN，則將其轉換為INT_MAX，避免溢出
        dividend = (is_dividend_int_min) ? INT_MAX : std::abs(dividend);
        divisor = std::abs(divisor);

        // 將divisor左移到與dividend相同位數，並且確保不會超過INT_MAX導致溢出
        int shifted_divisor = divisor;
        while (shifted_divisor <= (INT_MAX >> 1) && (shifted_divisor << 1) < dividend) {
            shifted_divisor <<= 1;
        }

        // 計算商，模擬binary長除法來實作
        int res = 0;
        while (shifted_divisor >= divisor) {
            if (dividend < shifted_divisor) {
                res <<= 1;
            }
            else {
                dividend -= shifted_divisor;
                res = (res << 1) + 1;
            }
            shifted_divisor >>= 1;
        }

        // 將res轉回正確的正負值
        res = is_negative ? -res : res;
        // 處理dividend是INT_MIN的極端情況，如果res是INT_MAX，則需要額外判斷res是否小於INT_MAX
        if (is_dividend_int_min && dividend + 1 == divisor && res < INT_MAX) {
            res = is_negative ? res - 1 : res + 1; // res為正就+1，res為負就-1
        }

        return res;
    }
};

// // 大神的方式
// class Solution {
//   public:
//     int divide(int dividend, int divisor) {
//         // 處理極端情況
//         if (divisor == 1) {
//             return dividend;
//         }
//         if (dividend == INT_MIN && divisor == -1) {
//             return INT_MAX;
//         }

//         // 當兩個數的符號位不同（即正負不同）時，dividend ^ divisor的最高有效位（MSB）會是1(表示負數)
//         bool is_negative = (dividend ^ divisor) < 0;
//         // 將兩數都轉為負數
//         dividend = dividend > 0 ? -dividend : dividend;
//         divisor = divisor > 0 ? -divisor : divisor;

//         // 計算商，模擬binary長除法來實作，只是由於兩數都轉為負數，因此判斷條件剛好相反
//         int ans = 0;
//         while (dividend <= divisor) {
//             int cnt = 1, shifted_divisor = divisor;
//             // 將shifted_divisor左移到與dividend相同位數，並且確保不會超過INT_MIN導致溢出
//             while (shifted_divisor >= (INT_MIN >> 1) && dividend <= (shifted_divisor << 1)) {
//                 shifted_divisor <<= 1;
//                 cnt <<= 1;
//             }
//             ans += cnt;
//             dividend -= shifted_divisor;
//         }

//         return is_negative ? -ans : ans;
//     }
// };

int main() {

    return 0;
}