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
        // TODO:浮點數誤差處理
        profit_rate > 0 ? profit_rate += 0.0000001 : profit_rate -= 0.00000001;
        std::cout << std::fixed << std::setprecision(2) << profit_rate << "% ";
        if (profit_rate >= 10 || profit_rate <= -7) {
            std::cout << "dispose" << '\n';
        }
        else {
            std::cout << "keep" << '\n';
        }
    }
    return 0;
}