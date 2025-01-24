#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int Tribonacci[38] = {0, 1, 1};
    int tribonacci(int n) {
        if (n == 0)
            return 0;
        if (Tribonacci[n] != 0)
            return Tribonacci[n];
        Tribonacci[n] = tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
        return Tribonacci[n];
    }
};

int main() { return 0; }