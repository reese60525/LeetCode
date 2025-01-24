/*
 * 題目： https://leetcode.com/problems/find-champion-ii/description/
 *
 * 題目解釋：
 * 給一個integer n代表有n個隊伍，一組2d integer array: edges = {{x1, y1}, {x2, y2}..., {xn, yn}}，
 * 代表一個有向圖，x和y各代表一個隊伍，其中對於每組{xi, yi}來說，yi這個隊伍比xi弱，求找出最強的隊伍(也就是沒有
 * 弱於任何隊伍)，若有一個以上的最強隊伍則return -1。
 *
 * 思路：
 * 用一個bool array紀錄每個隊伍的狀態，初始化為true，代表該隊伍是最強的(沒有其他隊伍比該隊伍強)，然後遍歷edges，
 * 將yi這個隊伍的bool設為false，因為yi比xi還要弱，最後遍歷bool array，若只有一個最強隊伍就return該隊伍，反之
 * 有一個以上的最強隊伍則return -1。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int findChampion(int n, std::vector<std::vector<int>> &edges) {
        bool is_champion[n]; // 紀錄當前隊伍是不是最強的
        std::memset(is_champion, 1, sizeof(is_champion));

        // 更新各個隊伍的狀態，將yi的隊伍的is_champion設為false
        for (auto &edge : edges) {
            is_champion[edge[1]] = false;
        }

        // 查找champion，若有一個以上則return -1
        int res = -1;
        for (int i = 0; i < n; ++i) {
            if (is_champion[i]) {
                if (res != -1) {
                    return -1;
                }
                res = i;
            }
        }

        return res;
    }
};

int main() {

    return 0;
}