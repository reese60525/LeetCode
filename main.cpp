/*
 * 題目:
 *
 * 題目解釋:
 *
 * 思路:
 *
 * 解法:
 *
 */
#include <iostream>

class Elevator {
  public:
    int state, cur, des;
    bool a1[21], a2[21], a3[21]; // a1儲存往上，a2儲存往下，a3儲存例外

    // constructor
    Elevator() {
        state = des = 0;
        cur = 1;
        memset(a1, 0, sizeof(a1));
        memset(a2, 0, sizeof(a1));
        memset(a3, 0, sizeof(a1));
    }

    // // 新增request
    // void add_request(int start, int end) {
    //     if (state == 0) { // 電梯當前狀態停止
    //         if (cur < start) {
    //             state = 1;
    //         }
    //         else if (cur > start) {
    //             state = 2;
    //         }
    //         else if (cur == start) {
    //             if (cur < end) {
    //                 state = 1;
    //                 a1[end] = true;
    //             }
    //             else {
    //                 state = 2;
    //                 a2[end] = true;
    //             }
    //             return;
    //         }
    //     }

    //     if (state == 1) { // 電梯當前狀態往上
    //         // 設定起始位置
    //         if (cur < start) { // 客戶位置在電梯路徑上
    //             a1[start] = true;
    //             if (start < end) { // 客戶目的地和電梯同方向
    //                 a1[end] = true;
    //             }
    //             else { // 客戶目的地和電梯反方向
    //                 a2[end] = true;
    //             }
    //         }
    //         else if (cur > start) { // 客戶位置在電梯路徑外
    //             a2[start] = true;
    //             if (start < end) { // 客戶目的地和電梯同方向
    //                 a3[end] = true;
    //             }
    //             else { // 客戶目的地和電梯反方向
    //                 a2[end] = true;
    //             }
    //         }
    //     }
    //     else if (state == 2) { // 電梯當前狀態往下
    //         // 設定起始位置
    //         if (cur > start) { // 客戶位置在電梯路徑上
    //             a2[start] = true;
    //             if (start > end) { // 客戶目的地和電梯同方向
    //                 a2[end] = true;
    //             }
    //             else { // 客戶目的地和電梯反方向
    //                 a1[end] = true;
    //             }
    //         }
    //         else if (cur < start) { // 客戶位置在電梯路徑外
    //             a1[start] = true;
    //             if (start > end) { // 客戶目的地和電梯同方向
    //                 a3[end] = true;
    //             }
    //             else { // 客戶目的地和電梯反方向
    //                 a1[end] = true;
    //             }
    //         }
    //     }
    // }
};

class Control {
  public:
    static void add_request(Elevator &e, int start, int end) {
        if (e.state == 0) { // 電梯當前狀態停止
            if (e.cur < start) {
                e.state = 1;
            }
            else if (e.cur > start) {
                e.state = 2;
            }
            else if (e.cur == start) {
                if (e.cur < end) {
                    e.state = 1;
                    e.a1[end] = true;
                }
                else {
                    e.state = 2;
                    e.a2[end] = true;
                }
                return;
            }
        }

        if (e.state == 1) { // 電梯當前狀態往上
            // 設定起始位置
            if (e.cur < start) { // 客戶位置在電梯路徑上
                e.a1[start] = true;
                if (start < end) { // 客戶目的地和電梯同方向
                    e.a1[end] = true;
                }
                else { // 客戶目的地和電梯反方向
                    e.a2[end] = true;
                }
            }
            else if (e.cur > start) { // 客戶位置在電梯路徑外
                e.a2[start] = true;
                if (start < end) { // 客戶目的地和電梯同方向
                    e.a3[end] = true;
                }
                else { // 客戶目的地和電梯反方向
                    e.a2[end] = true;
                }
            }
        }
        else if (e.state == 2) { // 電梯當前狀態往下
            // 設定起始位置
            if (e.cur > start) { // 客戶位置在電梯路徑上
                e.a2[start] = true;
                if (start > end) { // 客戶目的地和電梯同方向
                    e.a2[end] = true;
                }
                else { // 客戶目的地和電梯反方向
                    e.a1[end] = true;
                }
            }
            else if (e.cur < start) { // 客戶位置在電梯路徑外
                e.a1[start] = true;
                if (start > end) { // 客戶目的地和電梯同方向
                    e.a3[end] = true;
                }
                else { // 客戶目的地和電梯反方向
                    e.a1[end] = true;
                }
            }
        }
    }
};

int main() {
    // 乘客請求電梯
    std::vector<std::vector<int>> request {
        {5,  3 },
        {3,  7 },
        {4,  18},
        {20, 11},
        {13, 6 },
        {4,  9 }
    };
    // 要在第n個單位時間發出請求
    std::vector<int> request_time {2, 3, 4, 7, 13, 22};

    Elevator e1, e2;
    int t = 0;
    while (t++ < 200) {
        if (t == request_time[0]) {
            int start = request[0][0], end = request[0][1];

            if (e1.state == 0 && e2.state == 0) { // 兩台都沒任務
                Control::add_request(e1, start, end);
            }
            else {
                int e1_distance = std::abs((2 * e1.des) - e1.cur - start);
                int e2_distance = std::abs((2 * e2.des) - e2.cur - start);

                if (e1_distance <= e2_distance) {
                    Control::add_request(e1, start, end);
                }
                else {
                    Control::add_request(e2, start, end);
                }
            }
        }
    }

    return 0;
}