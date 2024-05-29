/*
 * 題目:
 * https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/description/
 *
 * 題目解釋:
 *
 * 思路:
 *
 * 解法:
 *
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int numSteps(std::string s) {
        int res = 0;
        while (s.length() != 1 || s[0] != '1') {
            if (s[s.length() - 1] == '0') {
                s.pop_back();
            }
            else {
                add_one(s);
            }
            ++res;
        }
        return res;
    }

  private:
    void add_one(std::string &s) {
        bool carry = true;
        for (int i = s.length() - 1; i > -1; --i) {
            if (carry) {
                if (s[i] == '1') {
                    s[i] = '0';
                    carry = true;
                }
                else {
                    s[i] = '1';
                    carry = false;
                }
            }
            else {
                break;
            }
        }
        if (carry) {
            s.insert(0, sizeof(char), '1');
        }
    }
};

int main() {
    return 0;
}