//
//  29.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/1/29.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;

const int MAXN = 100 + 10;
const int MAXM = 10 + 5;
const int MAX = (1 << 10) - 1 + 10;

int status[MAX], dp[2][MAX][MAX], can[MAXN];
int cnt, n, m;
char str[MAXM];

inline int pop(int x) {
    int ret = 0;
    while(x) {
        if(x & 1) ret++;
        x >>= 1;
    }
    return ret;
}

inline int Check(int a, int b) {
    return a & b;
}

inline int Check3(int a, int b, int c) {
    return Check(a,b) || Check(a,c) || Check(b,c);
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n;i++) {
        scanf("%s",str + 1);
        for(int j = 1;j <= m;j++)
            if(str[j] == 'H')can[i] = (can[i] << 1) | 1;
            else can[i] = can[i] << 1;
    }
    for(int i = 0; i <= (1 << m) - 1; i++) {
        if((!(i & (i << 2))) && (!(i & (i << 1))))
            status[++cnt] = i;
    }
    for(int i = 1;i <= cnt;i++)
        dp[1 % 2][i][1] = pop(status[i]);
    
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= cnt; j++) {
            if (!(status[j] & can[i])) {
                for (int k = 1; k <= cnt; k++) {
                    if ((!(status[k] & can[i - 1])) && (!Check(status[j],status[k]))) {
                        for (int l = 1; l <= cnt; l++){
                            if ((!(status[l] & can[i - 2])) && (!Check3(status[j], status[k], status[l])))
                                dp[i % 2][j][k] = std::max(dp[i % 2][j][k], dp[(i - 1) % 2][k][l] + pop(status[j]));
                        }
                    }
                }
            }
        }
    }
    
    int ans = 0;
    for(int i = 1; i <= cnt; i++)
        for(int j = 1; j <= cnt; j++)
            ans = std::max(ans, dp[n % 2][i][j]);
    printf("%d\n", ans);
    return 0;
}
