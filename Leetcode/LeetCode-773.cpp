/*
 * 題目： https://leetcode.com/problems/sliding-puzzle/description/
 *
 * 題目解釋：
 * 給一個2*3整數matrix，elements為0~5，target為{{1, 2, 3}, {4, 5, 0}}，對於0這個element
 * 可以與其鄰近(上下左右)的element交換，求得到target最少需要移動幾次。
 *
 * 思路：
 * 關鍵字:"最小"移動次數，可以用bfs來處理，將matrix的每個排列組合當作一個狀態，每次處理一個狀態，
 * 將其接下來可以得到的狀態放入queue中，並用hash_map來判斷是否已經走過，直到queue為空或是找到
 * target。
 */
#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int slidingPuzzle(std::vector<std::vector<int>> &board) {
        int dir[5] = {0, 1, 0, -1, 0};
        using PuzzleState = std::array<std::array<int, 3>, 2>;
        PuzzleState start;
        PuzzleState target = {
            {{1, 2, 3}, {4, 5, 0}}
        };
        // 初始化起始狀態
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 3; ++j) {
                start[i][j] = board[i][j];
            }
        }

        // q存放當前可走到的狀態，visited存放已走過的狀態
        std::queue<PuzzleState> q;
        std::set<PuzzleState> visited;
        q.push(start);
        visited.insert(start);

        int res = 0; // 移動步數

        // bfs
        while (!q.empty()) {     // 當q為空時，代表所有狀態都已走過
            int size = q.size(); // bfs，一次處理一層，所以這裡要先記錄q的size
            // 因為q.size()在迴圈中變化，如果用i < q.size()會導致錯誤
            for (int i = 0; i < size; ++i) {
                // 取出q的第一個element
                PuzzleState cur = q.front();
                q.pop();

                // 如果當前狀態等於目標狀態，回傳步數
                if (cur == target) {
                    return res;
                }

                // 找出0的位置
                int x, y;
                for (int idx = 0; idx < 6; ++idx) {
                    if (cur[idx / 3][idx % 3] == 0) {
                        x = idx / 3;
                        y = idx % 3;
                        break;
                    }
                }

                // 將0與周圍的數字交換
                for (int j = 0; j < 4; ++j) {
                    int nx = x + dir[j];
                    int ny = y + dir[j + 1];
                    if (nx < 0 || nx > 1 || ny < 0 || ny > 2) { // 判斷是否超出範圍
                        continue;
                    }

                    // 交換，得到新的狀態
                    PuzzleState next = cur;
                    std::swap(next[nx][ny], next[x][y]);

                    // 如果新的狀態已經走過，跳過
                    if (visited.find(next) != visited.end()) {
                        continue;
                    }

                    // 將新的狀態加入q和visited
                    q.push(next);
                    visited.insert(next);
                }
            }
            ++res; // 當前層的狀態都已經處理完，步數加1
        }

        return -1; // 如果沒有找到解，回傳-1
    }
};

int main() {

    return 0;
}