/*
 * 題目: https://leetcode.com/problems/search-in-rotated-sorted-array/description/
 *
 * 題目解釋:
 * 有一個原本是升序排序的整數array，給定一個pivot_index，大小為1到array.size()-1，從pivot_index之
 * 後的element移至左邊(包含pivot_index)，EX: nums = {1 ,2 ,3 ,4 ,5 ,6 ,7 ,8, 9}，pivot_index
 * = 5，nums[pivot_index] = 6，則旋轉後的nums為{6, 7, 8, 9, 1 ,2 ,3 ,4 , 5}。給一個array nums
 * nums可能會旋轉可能不會，給一個target，求target在nums中的index，若是找不到則return -1。
 * 題目要求時間複雜度必須為"O(logn)"。
 *
 * 思路:
 * 找數字，時間複雜度要O(logn)，很明顯是用binary search。
 *
 * 解法:
 * 分成兩次binary search，第一次找出nums的最小值的index，即為旋轉前的nums開頭，假設nums旋轉後為
 * {6, 7, 8, 9, 1 ,2 ,3 ,4 , 5}，第一次binary search找到最小值為1，index在4，我們可以透過擴展旋轉後的
 * nums，像是這樣:{6, 7, 8, 9, 1 ,2 ,3 ,4 , 5, 6, 7, 8, 9, 1, 2 ,3 ,4}，以最小的數字為開頭，可以觀
 * 察可以透過(min_index + k) % n得到原本的升序array的index，其中k為任意數，n為nums的size。第二次bs找
 * target即可用此公式來定義mid。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int search(std::vector<int> &nums, int target) {
        int n = nums.size(), l = 0, r = nums.size() - 1;

        // binary search 找最小值，也就是原本array的開頭
        // 做完後l的值就是最小的nums的index
        while (l < r) {
            int mid = l + (r - l) / 2;

            if (nums[mid] > nums[r]) {
                l = mid + 1;
            }
            else {
                r = mid;
            }
        }

        r = (n - 1) + l; // 把nums向右擴展，l即為nums旋轉後再最小值左邊的num個數
        while (l <= r) {
            int mid = l + (r - l) / 2; // 這是從最小值index到擴展後的nums去找
            int real_mid = mid % n;    //% nums原本大小則會得到一個循環的index

            if (nums[real_mid] == target) {
                return real_mid;
            }
            if (nums[real_mid] > target) {
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
        return -1;
    }
};

int main() { return 0; }