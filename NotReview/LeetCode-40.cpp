/*
 * 題目： https://leetcode.com/problems/combination-sum-ii/description/
 *
 * 題目解釋：
 * 給一個整數 array 和 整數 target，array 中的每個 element 只能被選取一次，找出所有
 * 組合使得總和等於 target，且每個組合中的元素不能重複。
 * e.g.
 * array = {10, 1, 2, 7, 6, 1, 5}，target = 8，res = {{1, 1, 6}, {1, 2, 5}, {1, 7}, {2, 6}}
 * 需要注意的是 {1, 2, 5} 和 {1, 7} 中的 `1` 可以由 array[1] 和 array[5] 中的 `1` 組成，而題目要求
 * 每個組合不能重複，因此只能用其中一個 `1` 來組成這兩個組合。
 *
 * 思路：
 * 使用backtracking algorithm。
 * 需要注意組合會有重複的問題，中心思想是把這些組合抽象成 tree 來看，每一個 level 的 node 是不能有重複的，
 * 以 array = {1, 1, 3}、target = 4為例子，tree 如下所示：
 *
 *            精簡版本             binary tree
 *             root                  root
 *         /     |  \  \         /         \
 *        1      1   3  x       1           x
 *      / | \   / \           /   \       /   \
 *     1  3  x 3   x         1     x     1     x
 *    / \                   / \   / \   / \   / \
 *   3   x                 3   x 3   x 3   x 3   x
 *
 * 共有八種路線，其中可以發現 {1, 3} 這個組合重複了兩次，觀察精簡版本的 tree 可以得到一個結論，對於 tree 的
 * 每一層而言，其 node 的 value 不可以重複，這樣能有效避免重複的組合。換個方式說明的話，組合 {1, 1, 3} 選用
 * 了array[0]和 array[1] 這兩個 1，而對於不選用 array[0] 且選用了 array[1] 的路線來看，這條路線 1 的數量
 * 不足以組成{1, 1, 3}，也就是說前面已經有路線含有更多相同的 element，這條路已經找到的組合包含了相同 element
 * 比較少的路線所能組成的組合，因此略過相同 element 較少的路線可以有效去除重複的組合。
 */

#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    void backtrack(std::vector<std::vector<int>> &res, std::vector<int> &temp, std::vector<int> &candidates, int target,
                   int index) {
        if (target < 0) {
            return;
        }
        if (target == 0) {
            res.push_back(temp);
            return;
        }

        for (int i = index; i < candidates.size(); ++i) {
            // 同一層的 value 不能重複遞迴，否則會產生重複的組合
            if (i > index && candidates[i] == candidates[i - 1]) {
                continue;
            }
            temp.push_back(candidates[i]);
            backtrack(res, temp, candidates, target - candidates[i], i + 1);
            temp.pop_back();
        }
    }
    std::vector<std::vector<int>> combinationSum2(std::vector<int> &candidates, int target) {
        std::sort(candidates.begin(), candidates.end());

        std::vector<int> temp;
        std::vector<std::vector<int>> res;
        // backtracking 找所有組合
        backtrack(res, temp, candidates, target, 0);

        return res;
    }
};

int main() {

    return 0;
}