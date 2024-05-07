#include <iostream>

template <int row, int column, int x>
void test(int (&array_2d)[row][column], int (&array_1d)[x]) {
    std::cout << "row:" << row << ", column" << column << '\n'; // 顯示array大小
    std::cout << "x:" << x << '\n';
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            std::cout << array_2d[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    for (int i = 0; i < x; ++i)
        std::cout << array_1d[i] << ' ';
}
int main() {
    int array_2d[5][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3}
    };
    int array_1d[6] = {1, 3, 5, 7, 9, 0};
    int x = 5;
    test(array_2d, array_1d);
    return 0;
}