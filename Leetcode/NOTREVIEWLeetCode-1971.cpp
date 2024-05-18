/*
 * 題目: https://leetcode.com/problems/find-if-path-exists-in-graph/
 * 題目解釋:
 * 思路:
 * 解法:
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    std::vector<int> parent;
    bool validPath(int n, std::vector<std::vector<int>> &edges, int source, int destination) {
        parent.resize(n);

        // initialize parent
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        // unite neighboring number
        for (const auto &i : edges) {
            unionFind(i[0], i[1]);
        }
        // if source and destination have same root, return true.
        return findRoot(source) == findRoot(destination);
    }

  private:
    int findRoot(int &x) {
        return x == parent[x] ? x : parent[x] = findRoot(parent[x]);
    }

    void unionFind(int x, int y) {
        parent[findRoot(x)] = findRoot(y);
    }
};
int main() {

    return 0;
}