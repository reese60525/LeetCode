#include <iomanip>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int n;
    double m, p;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> m >> p;
        double profit_rate = (p - m) / m * 100;
        // 浮點數誤差處理
        // 當除法商數超過能儲存的範圍時會無條件捨去，題目所求的是四什五入的結果
        // 當profit_rate = 2.4999999999999999時，應該輸出2.50
        // 但由於除法商數的overflow是無條件捨去，輸出會變成2.49
        // 因此需要自己處理浮點數誤差，加減一個相對小的值來進位
        profit_rate >= 0 ? profit_rate += 0.0000001 : profit_rate -= 0.0000001;
        std::cout << std::fixed << std::setprecision(2) << profit_rate + 0.0 << "% ";
        if (profit_rate >= 10.00 || profit_rate <= -7.00) {
            std::cout << "dispose" << '\n';
        }
        else {
            std::cout << "keep" << '\n';
        }
    }
    return 0;
}