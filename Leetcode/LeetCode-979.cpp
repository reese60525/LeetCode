/*
 * 題目: https://leetcode.com/problems/distribute-coins-in-binary-tree/description/
 *
 * 題目解釋:
 * 給一個binary tree，每個node的value(金幣數量)為0~n，n為node數量，所有節點的value(金幣數量)相加剛好
 * 等於n，每一個金幣移動到相鄰node所需要的路徑成本為1，讓所有node都剛好分配到一個金幣，求最小路徑成本。
 *
 * 思路:
 * 把問題拆成數個subtrees，從leaf node開始看，如果value為0代表還缺1個硬幣，value為1剛剛好，value為2或
 * 以上則代表多出硬幣，可以把目前缺或多幾個硬幣傳回給parent node，公式為node_value - 1，缺1個硬幣則return
 * -1，剛好1個return 0，以此類推。從parent node來看，若左或右node非nullptr，則遞迴拆解成subtrees，
 * return回來的值則是代表左或右node目前缺或多幾個硬幣，而每個硬幣移動到鄰近node的成本則是以回傳的值來算，
 * 如果回傳-3，表示缺3個硬幣，移入3個硬幣到subtrees的路徑成本就是3，反正如果是+3，表示多出3個硬幣，要分配給
 * 其他人的路徑成本也是3，路徑成本和硬幣數量都會從leaf node一路往parent node回傳。
 *
 * 解法:
 * dfs遍歷到leaf node，再根據上述思路去解，層層回傳目前硬幣需求和累加路徑成本。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
  public:
    int distributeCoins(TreeNode *root) {
        int res = 0; // 路徑成本
        dfs(root, res);
        return res;
    }

  private:
    int dfs(TreeNode *root, int &res) {
        int l = 0, r = 0; // 左右節點的回傳值，代表各自缺或多幾個硬幣
        if (root->left != nullptr) {
            l = dfs(root->left, res);
        }
        if (root->right != nullptr) {
            r = dfs(root->right, res);
        }
        res += std::abs(l) + std::abs(r); // 路徑成本為缺或多的硬幣數量
        return (root->val - 1) + l + r;   // 合併左右節點的硬幣，再算上自身缺或多幾個硬幣
    }
};

int main() {

    return 0;
}