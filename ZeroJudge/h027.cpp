#include <iostream>
#include <vector>
static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int matrix_range[2][2], max_diff_count, min_sum_diff = 100000000, coMatrix_count = 0;
std::vector<std::vector<int>> matrix[2];

void co_matrix(int row, int column) {
    int diff_count = 0, sum_diff = 0;
    for (int i = 0; i < matrix_range[0][0]; ++i) {
        int temp = column;
        for (int j = 0; j < matrix_range[0][1]; ++j) {
            if (matrix[1][row][temp] != matrix[0][i][j]) {
                ++diff_count;
                sum_diff += (matrix[1][row][temp] - matrix[0][i][j]);
            }
            if (diff_count > max_diff_count)
                return;
            ++temp;
        }
        ++row;
    }
    ++coMatrix_count;
    min_sum_diff = abs(sum_diff) < min_sum_diff ? abs(sum_diff) : min_sum_diff;
}

int main() {
    std::cin >> matrix_range[0][0] >> matrix_range[0][1] >> matrix_range[1][0] >> matrix_range[1][1] >> max_diff_count;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < matrix_range[i][0]; ++j) {
            std::vector<int> temp;
            for (int k = 0; k < matrix_range[i][1]; ++k) {
                int m;
                std::cin >> m;
                temp.push_back(m);
            }
            matrix[i].push_back(temp);
        }
    }

    for (int i = 0; i <= matrix_range[1][0] - matrix_range[0][0]; ++i) {
        for (int j = 0; j <= matrix_range[1][1] - matrix_range[0][1]; ++j) {
            co_matrix(i, j);
        }
    }

    min_sum_diff = coMatrix_count == 0 ? -1 : min_sum_diff;
    std::cout << coMatrix_count << '\n' << min_sum_diff << '\n';
    return 0;
}