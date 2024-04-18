#include <iostream>
#include <vector>

using namespace std;

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

void recursive_ans(vector<string> &ans, int n, int left_count, int right_count, string temp) {
    // cout << "left_count= " << left_count << ", right_count= " << right_count << ", temp= " <<
    // temp
    //  << '\n';

    if (left_count == n && right_count == n) {
        ans.push_back(temp);
    }
    if (left_count < n)
        recursive_ans(ans, n, left_count + 1, right_count, temp + '(');
    if (right_count < left_count)
        recursive_ans(ans, n, left_count, right_count + 1, temp + ')');
}
vector<string> generateParenthesis(int n) {
    vector<string> ans;
    recursive_ans(ans, n, 0, 0, "");
    return ans;
}

int main() {
    vector<string> ans = generateParenthesis(3);
    for (auto i : ans) {
        cout << i << " ";
    }
    return 0;
}