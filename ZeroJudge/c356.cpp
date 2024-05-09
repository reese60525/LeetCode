/*
 * getchar()介紹:
 * 解法 : https://reurl.cc/1v10NW
 */
#include <iostream>

int main() {
    int n;
    while (std::cin >> n) {
        std::getchar(); // 用來擷取'\n'字元
        for (int i = 0; i < n * n; ++i) {
            char c = std::getchar();
            if (i % n == i / n) // row and column相等
                std::cout << c;
        }
        std::cout << '\n';
    }
    return 0;
}