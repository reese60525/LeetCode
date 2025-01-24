/*
 * 題目： https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/description/
 *
 * 題目解釋：
 * 給一個整數array，找出最短subarray使array將該subarray移除後，剩下的array會是升序數組。
 * e.g. 假設arr = {1, 2, 3, 3, 3, 3, 3, 3, 3, 10, 11, 12, 0, 1, 2, 7, 7, 7, 7, 7, 7, 7, 8, 9}
 * 將{10, 11, 12, 0, 1, 2}移除即可得升序數組{1, 2, 3, 3, 3, 3, 3, 3, 3, 7, 7, 7, 7, 7, 7, 7, 8, 9}
 *
 * 思路：
 * 尋找array中arr[0]開頭的前綴和arr[arr.size()-1]結尾的後綴之最長升序數組，並試著將前綴和後綴合成
 * 一個升序數組，該合成數組要為捨棄最少element的升序數組。
 *
 * e.g. array = {1, 3, 4, 5, 6, 6, 7, 8, 87, 88, 3, 3, 4}，res為答案。
 * 前綴 = {1, 3, 4, 5, 6, 6, 7, 8}，前綴在array中結尾的index: prefix = 7，
 * 後綴 = {3, 3, 4}，後綴在array中起始的index: suffix = 10。
 * 接著初始化res，可以選擇其中一個數組來保留，並捨棄其餘的部分，
 * 例如選擇保留前綴，捨棄{87, 88, 3, 3, 4}，因此res = n - 1 - prefix = 5，
 * 或選擇保留後綴，捨棄{1, 3, 4, 5, 6, 6, 7, 8, 87, 88}，因此res = suffix = 10，
 * 此這兩種情況中取捨棄元素較少的，因此初始的res = 5。
 * 然後將兩個數組從頭開始遍歷，組合成一個升序數組，並計算捨棄的element數量，l和r為前綴、後綴的起始index，
 * 若arr[l] <= arr[r]，表示arr[l]結尾的前綴可以和arr[r]開頭的後綴組成升序數組，
 * 將arr[l]和arr[r]之間的element當作可捨棄的，計算這之間element數量並更新res，
 * 將l向右移動，繼續尋找下一個可以和arr[r]開頭的後綴組成升序數組的前綴。
 * 當arr[l] = 1時，可以組成升序數組{1, 3, 3, 4}，
 * 當arr[l] = 3時，可以組成升序數組{1, 3, 3, 3, 4}，
 * 當arr[l] = 4時，可以組成升序數組{1, 3, 4, 4}，
 * 當arr[l] = 5時，會跳出迴圈，因為後綴的element都比arr[l]小，沒辦法和後綴組合成升序數組
 * 若arr[l] > arr[r]，表示arr[l]結尾的前綴不能和arr[r]開頭的後綴組成升序數組，
 * 因此arr[r]必須被捨棄，將r向左移動，繼續尋找下一個可以和arr[l]結尾的前綴組成升序數組的後綴。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int findLengthOfShortestSubarray(std::vector<int> &arr) {
        int res = 0, n = arr.size();
        int prefix = 0, suffix = n - 1; // 最長升序數組前綴的結尾index和後綴的起始index

        // 尋找最長升序數組前綴的結尾index
        while (prefix < n - 1 && arr[prefix] <= arr[prefix + 1]) {
            ++prefix;
        }

        // 若最長升序數組前綴的結尾index在arr的最後一個element，表示整個arr都是升序數組
        if (prefix == n - 1) {
            return 0;
        }

        // 尋找最長升序數組後綴的起始index
        while (suffix > 0 && arr[suffix] >= arr[suffix - 1]) {
            --suffix;
        }

        // 初始化res，可以選擇其中一個數組來保留，並捨棄其餘的部分，選捨棄較少的element數量給res
        res = std::min(n - 1 - prefix, suffix);

        // 將兩個數組從頭開始遍歷，組合成一個升序數組，並計算捨棄的element數量
        int l = 0, r = suffix; // 數組各自的起始index
        while (l <= prefix && r < n) {
            if (arr[l] <= arr[r]) {
                res = std::min(res, r - l - 1);
                ++l;
            }
            else {
                ++r;
            }
        }

        return res;
    }
};

int main() {

    return 0;
}