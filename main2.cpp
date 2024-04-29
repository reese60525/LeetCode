#include <algorithm>
#include <iostream>

template <int N>
void printArray(std::string (&array)[N]) {
    for (auto i : array)
        std::cout << i << ' ';
    std::cout << '\n';
}

int main() {
    std::string a[]("1", "55555", "333", "22", "7777777", "666666");
    std::string b[]("333", "22", "666666", "1", "7777777", "88888888");
    printArray(a);
    printArray(b);
    // 方法1
    std::sort(std::begin(a), std::end(a), [](std::string &a, std::string &b) {
        return a.length() > b.length();
    });
    printArray(a);
    // 方法2
    std::ranges::sort(b, std::greater {}, &std::string::size);
    printArray(b);
    return 0;
}