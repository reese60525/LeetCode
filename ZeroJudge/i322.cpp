#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 解題思路:
// N個塔要從A移到C的話要先把上面N-1個塔從A移到B，接著把最底下的塔從A移到C，最後把N-1個塔從B移到C
// N-1個塔要從A移到B的話要先把上面N-2個塔從A移到C，接著把最底下的塔從A移到B，最後把N-2個塔從C移到B
// ...以此類推，直到最底下的塔和最上面的塔一樣(也就是該stack只有一個塔)，輸出移動結果並return回上個遞迴
void hanoi(int n, int top, char from, char to) {
    if (n == top) {
        std::cout << "Move disc " << top << " from " << from << " to " << to << '\n';
        return;
    }
    if (from == 'A' && to == 'C') {
        hanoi(n - 1, top, 'A', 'B');
        hanoi(n, n, 'A', 'C');
        hanoi(n - 1, top, 'B', 'C');
    }

    else if (from == 'A' && to == 'B') {
        hanoi(n - 1, top, 'A', 'C');
        hanoi(n, n, 'A', 'B');
        hanoi(n - 1, top, 'C', 'B');
    }
    else if (from == 'B' && to == 'A') {
        hanoi(n - 1, top, 'B', 'C');
        hanoi(n, n, 'B', 'A');
        hanoi(n - 1, top, 'C', 'A');
    }
    else if (from == 'B' && to == 'C') {
        hanoi(n - 1, top, 'B', 'A');
        hanoi(n, n, 'B', 'C');
        hanoi(n - 1, top, 'A', 'C');
    }
    else if (from == 'C' && to == 'A') {
        hanoi(n - 1, top, 'C', 'B');
        hanoi(n, n, 'C', 'A');
        hanoi(n - 1, top, 'B', 'A');
    }
    else if (from == 'C' && to == 'B') {
        hanoi(n - 1, top, 'C', 'A');
        hanoi(n, n, 'C', 'B');
        hanoi(n - 1, top, 'A', 'B');
    }
}

int main() {
    int n;
    while (std::cin >> n) {
        hanoi(n, 1, 'A', 'C');
    }
    return 0;
}