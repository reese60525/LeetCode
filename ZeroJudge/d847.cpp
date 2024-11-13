/*
 * 題目： https://zerojudge.tw/ShowProblem?problemid=d847
 *
 * 題目解釋：
 * 給平面上n個點的x和y座標，算出每個點的rank並依照輸入的順序印出rank。
 *
 * 思路：
 * 用divide and conquer來做，首先依照x座標來排序points，找出x座標上的中位數並分割，
 * 接著再將分割後的兩子集繼續做divide and conquer，recursion終止條件為當子集大小<=1，
 * 將該子集的point的rank設為0然後結束recursion，接著將兩子集依照y座標排序，然後把右子
 * 集的rank加總到左子集的rank。
 */
#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
    double x, y;
    int rank, index;
};

// 2-D ranking finding algorithm
void rankingFinding(std::vector<Point> &points, std::vector<int> &ranks) {
    // recursion終止條件
    if (points.size() <= 1) {
        if (!points.empty()) {
            points[0].rank = 0;
        }
        return;
    }

    // 將points排序後找出x座標的中位數
    std::sort(points.begin(), points.end(), [](Point a, Point b) {
        return a.x < b.x;
    });
    int n = points.size();
    double x_median = (n % 2 == 0) ? (points[n / 2 - 1].x + points[n / 2].x) / 2 : points[n / 2].x;

    // 將points分成兩個子集
    std::vector<Point> left, right;
    for (int i = 0; i < n; ++i) {
        if (points[i].x < x_median) {
            left.push_back(points[i]);
        }
        else {
            right.push_back(points[i]);
        }
    }

    // 當points的x座標全部相同時會出現left為空，right擁有所有的point的情況
    // 這是因為前面將points分成兩個子集的判斷條件為，x座標 < median的point會在left，反之在right
    // 又由於right的所有的point的x座標都相同，其median相等於所有point的x座標
    // 因此會造成rakingFinding(right)會無限遞迴
    // 所以當某個子集為空時，要平均分配point給兩個子集
    if (left.empty() || right.empty()) {
        left.clear();
        right.clear();
        for (int i = 0; i < n / 2; ++i) {
            left.push_back(points[i]);
        }
        for (int i = n / 2; i < n; ++i) {
            right.push_back(points[i]);
        }
    }

    // 遞迴呼叫rankingFinding繼續找尋子集的rank
    rankingFinding(left, ranks);
    rankingFinding(right, ranks);

    // 遞迴完成後，將子集依照y座標排序
    double left_max_x = left[left.size() - 1].x; // 左子集的最大x座標
    std::sort(left.begin(), left.end(), [](Point a, Point b) {
        return a.y < b.y;
    });
    std::sort(right.begin(), right.end(), [](Point a, Point b) {
        return a.y < b.y;
    });

    // 將右子集的rank加總左子集的rank
    // 當left的point的x座標與right的point的x座標相同時(也就是left.x = right.x = left_max_x)
    // 此時的right的point的rank值不可以累加上該left的point，e.g. left = (1,1)和right = (1,2)
    // 因此要將left.x = left_max_x的情況分開計算其累加的count
    // 若right.x = left_max_x，只能讓right.rank累加 left.x != left_max_x的count
    // 反之right.x != left_max_x，則要讓right.rank累加 left.x != left_max_x 和 left.x = left_max_x的count
    int same_x_count = 0, not_same_x_count = 0; // 分別計算當x座標相同和不同時，left的point的累加數量
    size_t left_index = 0, right_index = 0;
    while (right_index < right.size()) { // 直到right的point全部累加完
        // 當left.y < right.y時，要累加left的point的count
        if (left_index < left.size() && left[left_index].y < right[right_index].y) {
            // 根據left.x是否等於left_max_x，決定要累加的count種類
            if (left[left_index].x == left_max_x) {
                ++same_x_count;
            }
            else {
                ++not_same_x_count;
            }
            ++left_index;
        }
        // 當left.y >= right.y時，將right.rank累加上left的point的count
        else {
            // 根據right.x是否等於left_max_x，決定要累加的count種類
            if (right[right_index].x == left_max_x) {
                right[right_index].rank += not_same_x_count;
            }
            else {
                right[right_index].rank += not_same_x_count + same_x_count;
            }
            ranks[right[right_index].index] = right[right_index].rank;
            ++right_index;
        }
    }

    // 合併兩個子集
    points = left;
    points.insert(points.end(), right.begin(), right.end());
}

int main() {
    int k;
    while (std::cin >> k) {
        std::vector<int> ranks(k, 0);
        std::vector<Point> points;

        for (int i = 0; i < k; ++i) {
            Point point;
            std::cin >> point.x >> point.y;
            point.index = i;
            points.push_back(point);
        }

        rankingFinding(points, ranks);

        for (int i = 0; i < k; ++i) {
            std::cout << ranks[i] << '\n';
        }
    }

    return 0;
}