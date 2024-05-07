#include <iostream>

template <int x1, int y1, int x2, int y2>
void printArray(int (&array1)[x1][y1], int (&array2)[x2][y2]) {
    std::cout << "array1:" << '\n';
    for (auto &i : array1) {
        for (auto &j : i) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    std::cout << "array2:" << '\n';
    for (auto &i : array2) {
        for (auto &j : i) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main() {
    int a[2][4] = {
        {1, 3, 5, 7},
        {2, 4, 6, 8}
    };
    int b[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    printArray(a, b);
    return 0;
}