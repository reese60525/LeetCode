/*
 * 解法:貪婪演算法，最大堆實現。
 * 首先理解題目意思，quality = [3, 1, 10, 10, 1]， wage = [4, 8, 2, 2, 7]， k = 3，接下來q表示quality，w表示wage，
 * 共要雇用3名員工，假設現在招聘index = 0的員工，q[0] = 3、w[0] = 4，由於我們給第1位員工$4工資， 也就是招聘該名員工所需要的
 * 最低工資w[0]，因此若是下一位要招聘的員工其q為x，w為y，那麼招聘他的成本為cost = (x / 3) * 4，並且cost必須大於等於y，簡單
 * 來說，因為第一位員工他的工作效率(品質)為3，你付了4元給他，那麼對於其他員工也要公平，所以以第一名員工的成本/效率(w/q)為基準來
 * 判斷其他員工該付多少錢，再進一步判斷這筆錢有沒有滿足最低薪資。
 *
 * 以暴力解來看，遍歷兩層for迴圈，範圍是q和w的size，第一層迴圈決定"基準員工價值"(也就是決定w/q是多少)，第二層迴圈則判斷每一位員工
 * 能不能招聘，若是能招聘並且目前招聘的人不足k(需要的員工數量)就列入招聘名單，若是能招聘且現在已經有k名招聘名單，就去比較目前這位員
 * 工和招聘名單中最高的"工資成本"誰比較小，如果現在這位員工比較小就把他加入名單，並把原本名單中的最大工資刪掉。由於q和w的size可達
 * 1e4，O(n^2)絕對TLE，所以暴力解行不通。
 *
 * 現在思考如何優化，上面有講到一個很重要的公式，也就是如何判斷員工能不能招聘，可以透過(q2 / q1) * w1 >= w2來決定，q1和w1即為
 * 基準員工的q和w(暴力解中的第一層for迴圈)，q2和w2就是新員工的，這公式簡單來說就是"新員工效率除以基準員工的效率"再乘以"基準員工薪
 * 資"， 若是算出來的薪資能夠滿足新員工的最低薪資w2，則可以判斷該員工能招聘，再把這個公式變換一下變成 (w1 / q1) >= (w2 / q2)，新
 * 員工的"員工價值"必須小於等於"基準員工價值"才能招聘，這樣我們就能透過此公式來完成題目。
 * 由上面公式知道每個員工的薪資由"基準員工價值"乘以"該員工的q"來決定，若是想取得最小成本，可以從最小的"基準員工價值"來計算，首先建立
 * 一個table，用來存放每個員工的"員工價值"也就是(w / q) 以及q，並且依照"員工價值"由小到大排序，然後建立一個最大堆，將table前k項
 * (index = 0 ~ index = k - 1，共k項)的q放入，然後計算目前最大堆的所有成本，用前面說到的公式cost = (q2 / q1) * w1一一累加
 * 即可得到目前最大堆的總成本，之後再從index = k開始遍歷table，若是新的q比最大堆的top(也就是最大的q)還小，則把新的q放入最大堆，
 * 並且移除原本的top，然後計算新的總成本是否小於最小總成本，遍歷完即可得到答案。
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    // // priority_queue的排序要用struct overload () 運算子，可視為普通function
    // // 此function用來維護最大堆
    // // 用不到(因為pq預設就是小到大)
    // struct cmp {
    //     bool operator()(const int &a, const int &b) { return a < b; }
    // };

    double mincostToHireWorkers(std::vector<int> &quality, std::vector<int> &wage, int k) {
        double ans = std::numeric_limits<double>::max();
        // 建立一個vector，存放的資料為pair，first為wage[i]/quality[i]，second則是quality[i]
        std::vector<std::pair<double, int>> table(quality.size());
        // build table
        for (int i = 0; i < quality.size(); ++i)
            table[i] = std::pair(1.0 * wage[i] / quality[i], quality[i]);
        // 依照wage[i]/quality[i]由小排到大
        sort(table.begin(), table.end());

        int pq_total = 0; // 用來計算最大堆的所有元素總和
        // std::priority_queue<int, std::vector<int>, cmp> pq; //用不到
        std::priority_queue<int> pq;
        // 初始化最大堆，題目要求k個工人，所以從0到k-1放入最大堆
        for (int i = 0; i < k; ++i) {
            pq_total += table[i].second; // 累加quality[]
            pq.emplace(table[i].second); // 把quality[]放入最大堆
        }
        // 初始化ans
        ans = std::min(ans, pq_total * table[k - 1].first);
        // 從index = k開始遍歷table，每當新的quality[i]比最大堆中的top還小，就把quality[i]放入，pop出top
        for (int i = k; i < table.size(); ++i) {
            if (pq.top() > table[i].second) { // 最大堆的top(也就是最大的quality)比新的quality[i]還大就替換掉
                pq_total -= pq.top();
                pq_total += table[i].second;
                pq.pop();
                pq.emplace(table[i].second);
                // 每次最大堆總數(pq_total)有改動時就要重新比較總花費，由於table[i].first(也就是wage[]/quality[])
                // 是由小排到大，若是pq_total不變，first變大，總花費是逐漸變大的，所以pq_total沒變化則ans沒必要去比較。
                ans = std::min(ans, pq_total * table[i].first);
            }
        }
        return ans;
    }
};
int main() {
    return 0;
}
