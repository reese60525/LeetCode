#include <iostream>
#include <string>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int recursive_solve(int len, std::string head_tail, std::string s, int k) {
    while (s.length() >= 0) {
        if (abs(head_tail[1] - s[0]) <= k) {}
    }
}
int longestIdealString(std::string s, int k) {
    int largest_len = 0;
    for (auto i : s) {
        std::string head_tail = "";
        head_tail.append(2, i);
        s.erase(s.begin());
        int return_len = recursive_solve(1, head_tail, s, k);
        largest_len = largest_len > return_len ? largest_len : return_len;
    }
    return largest_len;
}
int main() {
    std::string s;
    int k;
    while (std::cin >> s >> k)
        std::cout << longestIdealString(s, k);
    return 0;
}