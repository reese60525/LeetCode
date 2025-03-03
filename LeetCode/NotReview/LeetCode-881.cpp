#include <algorithm>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// two pointer + 貪婪演算法， 重點是別想得太複雜!看"當前"最佳解就好!
class Solution {
  public:
    int numRescueBoats(std::vector<int> &people, int limit) {
        int ans = 0;
        std::sort(people.begin(), people.end()); // 由小排到大
        int l = 0, r = people.size() - 1;
        while (l <= r) {
            if (people[l] + people[r] <= limit) { // 能兩人上船就上
                ++l;
                --r;
            }
            else // 如果不能兩人上船，那就體重大的上
                --r;
            ++ans; // 每回合都要出航
        }
        return ans;
    }
};
int main() {
    Solution solution;
    std::vector<int> people = {187, 190, 291, 385, 445, 477, 576, 597, 613, 657};
    int limit = 1000;
    std::cout << solution.numRescueBoats(people, limit);
    return 0;
}