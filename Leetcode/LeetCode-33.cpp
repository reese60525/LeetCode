/*
 * 題目： https://leetcode.com/problems/search-in-rotated-sorted-array/description/
 *
 * 題目解釋：
 * 給一個 ascending order integer array，但是題目給的 array 可能有或沒有經過 rotate，
 * 例如：array = {0, 1, 2, 3, 4, 5, 6, 7}，rotate 後可以是 {3, 4, 5, 6, 7, 0, 1, 2}、
 * {7, 0, 1, 2, 3, 4, 5, 6}、{1, 2, 3, 4, 5, 6, 7, 0}、{0, 1, 2, 3, 4, 5 ,6, 7}...
 * 要從這樣的 array 找出 integer target，找到 return target 在 array 的 index，找不到
 * 則 return -1。
 * 題目要求時間複雜度必須是 O(log n)。
 *
 * 思路：
 * O(log n)可以使用 binary search。
 * 對於一個 rotated array = {5, 6, 7, 0, 1, 2, 3, 4}，我們可以將其視為兩個升序區塊組成，
 * {5, 6, 7} + {0, 1, 2, 3, 4}，簡稱為 left block and right block。可以發現 right block
 * 中的任何 element 都小於 left block，並且各自 block 中的 element 都是 ascending order。
 *
 * 方法 1：
 * 假設 array = {5, 6, 7, 0, 1, 2, 3, 4}，直接對 array 進行 binary search，分成三種情況：
 * 1. array[mid] = target，retrun mid。
 * 2. array[l] <= array[mid]，表示 l and mid 形成的 block 為 ascending order，
 * e.g. {5, 6} + {7, 0, 1, 2, 3, 4}，此時有兩種情況：
 *        |             |_____________________
 *        |--> l 和 mid 之間的 element        |--> mid + 1 和 r 之間的 element
 *    2-1. target 在這個 block 之間，則 r = mid - 1，對這個 block 進行搜尋。
 *    2-2. target 不在該 block 之間，則 l = mid + 1，搜索範圍排除掉這個 block。
 * 3. array[l] > array[r]，表示 mid and r 形成的 block 為 ascending order，
 * e.g. {5, 6, 7, 0, 1} + {2, 3, 4}，此時有兩種情況：
 *             |               |______________________
 *             |--> l 和 mid - 1 之間的 element       |--> mid 和 r 之間的 element
 *    3-1. target 在這個 block 之間，則 l = mid + 1，對這個 block 進行搜尋。
 *    3-2. target 不在該 block 之間，則 r = mid - 1，搜索範圍排除掉這個 block。
 *
 * 方法 2：
 * 假設 真實 array = {5, 6, 7, 0, 1, 2, 3, 4}，我們可以將此 array 進行"假想擴展"，
 * 而 擴展後 array = {5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7}。
 * 首先找出rotate之前 array 的 起始點 pivot，在此例子中 pivot 的 index = 3，
 * 以 pivot 為起點來"假想擴展" array，在這樣的 array 中對於 l 和 r 的操作都是
 * 以 pivot 到 擴展 array 的終點來做。設 l = pivot and r = pivot + array_size - 1，
 * l and r 都是"假想擴展" array 的 index，mid = l + (r - l) / 2，mid 也是"假想擴展"
 * array 的 mid，而 real_mid = mid % array_size，real_mid 是從"假想擴展" array 的
 * mid 映射到"真實情況"中的 mid，比如 l = 8 and r = 10 and mid = 9 and real_mid = 1，
 * 在"假想擴展"的 array[9] = 6，而"真實情況"中的 array[1] = 6，以這樣的方式來找尋 target。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// 　方法 1
class Solution {
  public:
    int search(std::vector<int> &nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            // 避免 l and r 都很大時發生整數溢位
            int mid = l + (r - l) / 2;

            // 找到 target， return index
            if (nums[mid] == target) {
                return mid;
            }
            // target 在 l and mid 形成的 ordered block 之間，進行搜索範圍壓縮
            if (nums[l] <= nums[mid]) {
                if (nums[l] <= target && target < nums[mid]) {
                    r = mid - 1;
                }
                else {
                    l = mid + 1;
                }
            }
            // target 在 mid and r 形成的 ordered block 之間，進行搜索範圍壓縮
            else {
                if (nums[mid] < target && target <= nums[r]) {
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }
        }

        // target 不存在於 nums 中
        return -1;
    }
};

// // 方法 2
// class Solution {
//   public:
//     int search(std::vector<int> &nums, int target) {
//         // 先找出 nums 最小的 element pivot，pivot 就是 nums rotate 之前的起始點
//         int pivot = 0;
//         int l = 0, r = nums.size() - 1;
//         while (l <= r) {
//             // 避免 l and r 都很大時發生整數溢位
//             int mid = l + (r - l) / 2;

//             // 只有 pivot 的左邊 element 才會大於 pivot
//             // 其餘任意兩個相鄰 element 都是右邊大於左邊的 element
//             if (mid < nums.size() - 1 && nums[mid] > nums[mid + 1]) {
//                 pivot = mid + 1;
//                 break;
//             }
//             // 由於 pivot 是 right block 的開頭
//             // 所以判斷 mid 在 left block 還是 right block 來進行搜索範圍壓縮
//             else if (nums[mid] >= nums[0]) {
//                 l = mid + 1;
//             }
//             else {
//                 r = mid - 1;
//             }
//         }

//         // 找到 pivot 後，將 nums 進行"假想擴展"來 binary search
//         l = pivot, r = pivot + nums.size() - 1;
//         while (l <= r) {
//             int mid = (l + r) / 2;            // "假想擴展"中的 mid index
//             int real_mid = mid % nums.size(); // "真實情況"中的 mid index

//             if (nums[real_mid] == target) {
//                 return real_mid;
//             }
//             // 對 l 和 r 的操作要以"假想擴展"的 mid 來做
//             else if (nums[real_mid] > target) {
//                 r = mid - 1;
//             }
//             else {
//                 l = mid + 1;
//             }
//         }

//         return -1;
//     }
// };

int main() {

    return 0;
}