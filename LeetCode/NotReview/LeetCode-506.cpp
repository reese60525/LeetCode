/*
 * radix sort的介紹 : https://reurl.cc/z1A9Ae
 * 解法參考 : https://reurl.cc/qVkENn
 * 解法1: 排序
 * 先遍歷nums，把(value,index)存入一個vector，再以value做降序排序，最後遍歷排序後
 * 的vector，根據pair中的index賦值給ans。
 * 使用std::sort的時間複雜度為o(nlogn)，想進一步提升效率可以用"radix sort"，
 * 測資數字大小為1e6以內，若是以十進制來看，一次只做1bit得要有9個bucket並且做七輪，
 * 若是想變成只做兩輪，那麼得要有10000個bucket(0~9999)，因為1e6為7bits，分成兩部分
 * 得要10000個bucket，例如1000000要分成，0100和0000，若是只有1000個bucket，那麼
 * 會變成000和000，少了第7bit。
 * 因此我們可以用二進制來看，2^20 = 2^10 * 2^10 = 1024 * 1024≒ 1e6，可以用1024個
 * bucket做兩輪排序，這樣做的時間複雜度為O(n+1024)。
 *
 * 解法參考 : https://reurl.cc/nN7K11
 * 解法2: 無排序
 * 題目說分數唯一(即不重複)，先找出最高分(max_score)，建個size為max_score+1的
 * value_to_index的vector，接著從max_score遍歷到0，若是在value_to_index中有找到
 * 該分數存在，就可以把排名push進ans中。這樣做的時間複雜度為O(n+m)，n = nums的size，
 * m為max_score。
 *
 * 就實際submit的結果來看，解法2會比較快，這也不易外，畢竟解法1遍歷nums6次(6n)，解法2
 * 則為2n+m次。
 */
#include <iostream>
#include <vector>

// 解法2
static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    std::vector<std::string> findRelativeRanks(std::vector<int> &score) {
        std::vector<std::string> ans(score.size(), "");
        // find max score
        int max_score = 0;
        for (auto i : score) {
            max_score = std::max(max_score, i);
        }
        // build table
        std::vector<int> score_to_index(max_score + 1, -1);
        for (int i = 0; i < score.size(); ++i) {
            score_to_index[score[i]] = i;
        }
        // build ans
        std::string medal[] {"Gold Medal", "Silver Medal", "Bronze Medal"};
        int index = 0;
        for (int i = max_score; i > -1; --i) {
            if (score_to_index[i] != -1) {
                if (index < 3) {
                    ans[score_to_index[i]] = medal[index];
                }
                else {
                    ans[score_to_index[i]] = std::to_string(index + 1);
                }
                ++index;
            }
        }
        return ans;
    }
};

// // 解法1
// static const auto io_sync_off = []() {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     return nullptr;
// }();
// class Solution {
//   public:
//     // change nums會做兩次，call function簡潔程式碼。
//     template <int N>
//     void change_nums(std::vector<std::pair<int, int>> &nums, std::vector<std::pair<int, int>> (&bucket)[N]) {
//         // 由於要做"降序"排序，因此從最尾端開始改。若是升序那index從0開始。
//         int index = nums.size() - 1;
//         for (auto &i : bucket) {
//             // 由於要做"降序"排序，因此從最尾端開始改。若是升序那j從0開始。
//             for (int j = i.size() - 1; j > -1; --j) {
//                 nums[index--] = i[j];
//             }
//             i.clear(); // 對std::vector<std::pair(value,index)做清除。
//         }
//     }
//     // radix sort;
//     void radix_sort(std::vector<std::pair<int, int>> &nums) {
//         std::vector<std::pair<int, int>> bucket[1024]; // 1024*1024 > 1e6(測資範圍)。
//         // first round
//         for (auto &i : nums) {
//             // 取二進位的後10bits, EX: 10010101 & 00001111 = 00000101
//             bucket[i.first & 1023].emplace_back(i);
//         }
//         change_nums(nums, bucket);
//         // second round
//         for (auto &i : nums) {
//             // 取二進位的前10bits, EX: 10010101 >> 4 = 1001
//             bucket[i.first >> 10].emplace_back(i);
//         }
//         change_nums(nums, bucket);
//     }
//     std::vector<std::string> findRelativeRanks(std::vector<int> &score) {
//         std::vector<std::string> ans(score.size());
//         std::vector<std::pair<int, int>> table;
//         // build table
//         for (int i = 0; i < score.size(); ++i)
//             table.emplace_back(score[i], i);
//         // sort table
//         radix_sort(table);
//         ans[table[0].second] = "Gold Medal";
//         if (score.size() > 1)
//             ans[table[1].second] = "Silver Medal";
//         if (score.size() > 2)
//             ans[table[2].second] = "Bronze Medal";
//         // build ans
//         for (int i = 3; i < score.size(); ++i) {
//             ans[table[i].second] = std::to_string(i + 1);
//         }
//         return ans;
//     }
// };
int main() { return 0; }