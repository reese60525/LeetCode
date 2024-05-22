/*
 * 題目: https://leetcode.com/problems/palindrome-partitioning/description/
 *
 * 題目解釋:
 * 給一個lowercase letter "s"，找出所有組合，每個組合的substring都是回文，並且組合起來能變成"s"。
 * EX: {a, a, a, b}所有可能組合為{{"a", "a", "a", "b"}, {"a", "aa", "b"}, {"aa", "a", "b"}
 * , {"aaa", "b"}}。
 *
 * 思路:
 * backtracking algorithm去解。
 *
 * 解法:
 * 每個level的backtracking找從傳入的index開始所有能成為回文的substring，找到後就進入下一層backtracking。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<std::vector<std::string>> partition(std::string s) {
        std::vector<std::vector<std::string>> res;
        std::vector<std::string> subs;

        backTracking(0, s, subs, res);
        return res;
    }

  private:
    void backTracking(int index, std::string &s, std::vector<std::string> &subs,
                      std::vector<std::vector<std::string>> &res) {
        if (index == s.length()) { // s已用完，把答案放入res
            res.push_back(subs);
            return;
        }

        std::string sub = ""; // 用以儲存substring
        for (int i = index; i < s.length(); ++i) {
            sub += s[i];
            if (checkPalindrome(sub)) { // 確認當前substring是不是回文
                subs.push_back(sub);
                backTracking(i + 1, s, subs, res); // 進入下個level
                subs.pop_back();
            }
        }
    }
    // 檢查string是否為回文
    bool checkPalindrome(std::string &sub) {
        int n = sub.length();
        for (int i = 0; i < n / 2; ++i) {
            if (sub[i] != sub[n - 1 - i]) { // 從頭和尾逐漸往中間檢查
                return false;
            }
        }
        return true;
    }
};

int main() { return 0; }