#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int set[1234567];
int findSet(int now) {
    if (set[now] != now)
        set[now] = findSet(set[now]);
    return set[now];
}
int n;
char str[123456];
int main() {
    int t;
    int i, j;
    int ans[2];
    scanf("%d", &t);
    gets(str);
    gets(str);
    while (t--) {
        scanf("%d", &n);
        gets(str);
        ans[0] = ans[1] = 0;
        for (i = 1; i <= n; ++i)
            set[i] = i;
        while (gets(str) && str[0] != '\0') {
            if (str[0] == 'c') {
                sscanf(&str[1], "%d %d", &i, &j);
                set[findSet(i)] = findSet(j);
            }
            else {
                sscanf(&str[1], "%d %d", &i, &j);
                if (findSet(i) == findSet(j))
                    ++ans[0];
                else
                    ++ans[1];
            }
        }
        printf("%d,%d\n", ans[0], ans[1]);
        if (t)
            puts("");
    }

    return 0;
}