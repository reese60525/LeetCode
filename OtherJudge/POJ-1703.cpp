/*
 * 題目: https://reurl.cc/QRZN99
 * 解法: 種類並查集
 * 敵人的敵人就是朋友，每次更新幫派狀態時，把自身的root和"敵人的敵人"的root相連即可。
 */
#include <cstdio>
#include <iostream>
#include <vector>

// connect用來表示誰和誰連接，opposition用來表示誰是誰的敵人(不同幫派)
std::vector<int> connect(1e5 + 1), opposition(1e5 + 1);
// find root，connect[a] = root(connect[a])可以順便更新所有人指向root，
// 能夠加快之後呼叫找root的速度
int root(int a) { return connect[a] == a ? a : connect[a] = root(connect[a]); }

// 用C的IO，不然會TLE
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= n + 1; ++i) // 初始化connect，讓所有人指向自己
            connect[i] = i;
        std::fill(opposition.begin(), opposition.end(), 0); // 初始化opposition為0
        while (m--) {
            char c;
            int a, b;
            // 這邊%c前面必須保留一個空格，不然%c會獨到緩衝區的剩餘空格。
            // stack overflow: https://reurl.cc/OMjQqy
            scanf(" %c%d%d", &c, &a, &b);
            if (c == 'A') {
                if (root(a) == root(b)) { // 兩人的root相同代表同幫派
                    printf("In the same gang.\n");
                }
                else if (root(a) == root(opposition[b])) { // 不能直接用彼此的root判斷，用b的敵人的root判斷才準確
                    printf("In different gangs.\n");
                }
                else { // 無法判斷是否同幫派或不同幫派
                    printf("Not sure yet.\n");
                }
            }
            else {
                if (opposition[a]) // 若op[a]不為0代表有人和他不同幫派，可以以此來給b更新root
                    connect[root(b)] = root(opposition[a]);
                if (opposition[b]) // 同上
                    connect[root(a)] = root(opposition[b]);
                opposition[a] = b; // 更新op[a]
                opposition[b] = a; // 同上
            }
        }
    }
    return 0;
}