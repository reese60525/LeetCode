#include <cmath>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main() {
    long long n;
    while (std::cin >> n) {
        std::string temp = std::to_string(n);
        int non_add_index;
        long long up = n, down = n;
        for (int i = 0; i < temp.length(); ++i) {
            if ((temp[i] - '0') % 2 == 0) {
                non_add_index = temp.length() - i; // 第幾位是非奇數，ex:1334000，non_add_index=4，也就是由右邊數來第四個數字(4)
                up = (n + pow(10, non_add_index - 1)) / (pow(10, non_add_index - 1));
                down = (n - pow(10, non_add_index - 1)) / (pow(10, non_add_index - 1));
                for (int j = 0; j < non_add_index - 1; ++j) {
                    up *= 10;
                    up += 1;
                    down *= 10;
                    down += 9;
                }
                if (temp[i] == '0') {
                    while (--i >= 0) {
                        if (temp[i] != '1') {
                            down = n / pow(10, temp.length() - i - 1) - 2;
                            // std::cout << down << '\n';
                            for (int j = 0; j < temp.length() - i - 1; ++j) {
                                down *= 10;
                                down += 9;
                            }
                            break;
                        }
                    }
                    if (i < 0) {
                        down = 0;
                        for (int j = 0; j < temp.length() - 1; ++j) {
                            down *= 10;
                            down += 9;
                        }
                        break;
                    }
                }
                break;
            }
        }
        // std::cout << "up=" << up << ", down=" << down << '\n';
        std::cout << ((up - n) < (n - down) ? up - n : n - down) << '\n';
    }
    return 0;
}
// 1311101
//  134 135
//  123 113 133
//  124 131
//  224 311 199
//  2724 3111 1999
//  52724 53111 51999
//  19902 19899 19911
//  11102 9991
//  1311101 1311099 1310999 1309999 1299999 1199999
//  1111101 999999