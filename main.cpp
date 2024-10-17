#include <iostream>

void quickSort(float *array, int l, int r) {
    int start = l, end = r;
    float pivot = array[start];

    // 進行排序，將比array[start]大和小的分成兩組
    while (l < r) {
        if (array[l] > pivot && array[r] < pivot) {
            std::swap(array[l], array[r]);
        }
        if (array[l] <= pivot) {
            ++l;
        }
        if (array[r] >= pivot) {
            --r;
        }
    }

    if (array[r] > pivot) { // 如果r當前的值比array[start]大，則將r向右移一個位置
        --r;
    }
    std::swap(array[start], array[r]); // 將array[start]擺到正確的位置

    if (start < r - 1) { // 若是右邊那組array的數字數量>=兩個再呼叫遞迴排序
        quickSort(array, start, r - 1);
    }
    if (end > r + 1) { // 若是左邊那組array的數字數量>=兩個再呼叫遞迴排序
        quickSort(array, r + 1, end);
    }
}

int main() {
    float array[] = {10, 5, 1, 5, 1, 1, 5, 26, 17, 14, 8, 7, 26, 21, 3};
    // int array[] = {1, 4, 2, 3};

    while (true) {
        int op, count, max_value, min_value;
        std::cout << "1執行快速排序法，執行插入排序法，3程式結束。\n請輸入要執行的動作:";
        std::cin >> op;

        if (op == 1) {
            quickSort(array, 0, (sizeof(array) / sizeof(array[0])) - 1);
        }
        else if (op == 2) {
            std::cout << "wait" << '\n';
        }
        else if (op == 3) {
            return 0;
        }

        // std::cout<<"1.所有數字數量:"
        for (float x : array) {
            std::cout << x << " ";
        }
    }
}