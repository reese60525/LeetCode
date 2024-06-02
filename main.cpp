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
#include <unordered_set>

class Elevator {
  private:
    int state = 0;          // 當前電梯行進狀態 0:空 1:上 2:下
    int requests_count = 0; // requests內的數量
    int requests[100][2]; // 電梯服務要求，[][0]為客戶樓層，[][1]為客戶目的地樓層
    int in_count = 0;
    int in[100]; // 客戶在電梯外按的樓層
    int out_count = 0;
    int out[100]; // 客戶在電梯內按的樓層
    int cur = 1;  // 電梯目前位置

  public:
    // 創建電梯物件時初始化array內容為0
    Elevator() {
        memset(requests, 0, sizeof(requests));
        memset(in, 0, sizeof(requests));
        memset(out, 0, sizeof(requests));
    }

    // 取得目前電梯要執行的request數量+requests array的數量
    int getCounts() {
        return requests_count + in_count + out_count;
    }

    // 新增request到requests array
    void newRequest(int begin, int end) {
        requests[requests_count][0] = begin;
        requests[requests_count][1] = end;
        ++requests_count;
    }

    void bubbleSort(bool reverse) {
        // 將重複樓層設為 0
        for (int i = 0; i < 100; ++i) {
            for (int j = i + 1; j < 100; ++j) {
                if (in[i] == in[j]) {
                    in[j] = 0;
                }
                if (out[i] == out[j]) {
                    out[j] = 0;
                }
            }
        }

        for (int i = 0; i < 100; ++i) {
            for (int j = i + 1; j < 100; ++j) {
                if ((reverse && in[i] < in[j]) || (!reverse && in[i] > in[j])) {
                    int temp = in[i];
                    in[i] = in[j];
                    in[j] = temp;
                }
                if ((reverse && out[i] < out[j]) || (!reverse && out[i] > out[j])) {
                    int temp = out[i];
                    out[i] = out[j];
                    out[j] = temp;
                }
            }
        }
    }

    void moveOneFloor(int counter) {
        std::cout << "count : " << counter << '\n';
        std::cout << "current floor : " << cur << '\n';
        for (auto &r : requests) {
            if (state == 0 && requests_count > 0) {
                in[0] = requests[0][0];
                out[0] = requests[0][1];
                // 設定電梯行進方向
                if (in[0] - out[0] > 0) {
                    state = 2;
                }
                else {
                    state = 1;
                }

                --requests_count;
                ++in_count;
                ++out_count;
            }
            if (state == 1) {}
        }
    }
};

int main() {
    int requests[][2] = {
        {2, 6},
        {4, 1},
        {6, 3},
        {5, 7},
        {8, 2},
        {2, 6},
        {7, 3},
        {4, 5},
        {2, 8}
    };
    Elevator e;

    int index = 0; // requests index
    int counter = 0;
    std::unordered_set<int> valid_cases = {0, 1, 2, 4, 7, 8, 12, 13, 19};
    while (e.getCounts() && index < 10) {
        if (valid_cases.find(counter) != valid_cases.end()) {
            e.newRequest(requests[index][0], requests[index][1]);
            ++index;
        }
        e.moveOneFloor();
        ++counter;
    }

    return 0;
}

// [%album artist% - ]['%album%[ CD%discnumber%][ #%tracknumber%]'- ]%title%[ '//' %track artist%]
// [%album artist% - ]['['%album%[ CD%discnumber%][ #%tracknumber%]']' ]%title%[ '//' %track
// %album artist% - %album% CD%discnumber%#%tracknumber% - %title%