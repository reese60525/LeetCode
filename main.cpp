#include <iostream>
#include <vector>
static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

void co_matrix(int row, int column, int matrix1_range[2], int max_dif_count, int min_sum_dif) {
    for (int i = 0; i < matrix1_range[0]; ++i) {
        for (int j = 0; j < matrix1_range[1]; ++j) {}
    }
}

int main() {
    int matrix1_range[2], matrix2_range[2], max_difference_count, min_sum_difference = 0;
    std::vector<int> matrix1;
    std::vector<std::vector<int>> matrix2;
    // input
    std::cin >> matrix1_range[0] >> matrix1_range[1] >> matrix2_range[0] >> matrix2_range[1] >> max_difference_count;
    for (int i = 0; i < matrix1_range[0]; ++i) {
        for (int j = 0; j < matrix1_range[1]; ++j) {
            int k;
            std::cin >> k;
            min_sum_difference -= k;
            matrix1.push_back(k);
        }
    }
    for (int i = 0; i < matrix2_range[0]; ++i) {
        std::vector<int> temp;
        for (int j = 0; j < matrix2_range[1]; ++j) {
            int k;
            std::cin >> k;
            temp.push_back(k);
        }
        matrix2.push_back(temp);
    }

    // output
    for (int i = 0; i <= matrix2_range[0] - matrix1_range[0]; ++i) {
        for (int j = 0; j <= matrix2_range[1] - matrix1_range[1]; ++j) {
            co_matrix(i, j, matrix1_range, max_difference_count, min_sum_difference);
        }
    }
    // output
    for (int i = 0; i < (matrix2_range[0] - matrix1_range[0]) * (matrix2_range[1] - matrix1_range[1]); ++i) {
        int now_matrix2_row_edge = matrix1_range[0];
        int now_matrix2_column_edge = matrix1_range[1];
        while (now_matrix2_row_edge <= matrix2_range[0]) {
            int now_matrix2_row_index = now_matrix2_row_edge - matrix1_range[0];
            int now_matrix2_column_index = now_matrix2_column_edge - matrix1_range[1];
            int now_difference_count = 0;
            while (now_matrix2_column_edge <= matrix2_range[1] && now_difference_count <= max_difference_count) {}
        }
    }
}