//
//  36.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/10/5.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define rap(a,s,t,i) for (int a = s; a <= t; a += i)
#define basketball(a,t,s,i) for (int a = t; a > s; a -= i)
#define countdown(s) while (s --> 0)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;

typedef long long int lli;

int getint() { int x; scanf("%d", &x); return x; }
lli getll() { long long int x; scanf("%lld", &x); return x; }

/**
 * 看见数据范围想到 O(n^3)
 * 设 dp[i][j] 表示编号在 [1, i] 中的村庄建立 j 个小学的最小距离
 * 转移方程？这么考虑：
 * 枚举断点 k，把整个区间分为 [1, k] 和 [k + 1, i]
 * 在左区间建立 j - 1 个小学，在右区间里仅建立一个小学
 * 所以转移方程是：
 * dp[i][j] = min{ dp[k][j - 1] + 在 [k + 1, i] 中建立一个小学的最小距离 | (j - 1 <= k <= i) }
 * 加号右边那个玩意怎么算？
 * 设 f[i][j] 表示编号在 [i, j] 中的村庄建立一个小学的最小距离
 * 由生活常识知道往中间建比较优（证明见 https://www.luogu.org/blog/AH2002/solution-p4677 ）
 * 所以 f[i][j] = \sum_{k = i}^{j} dis(k, (i + j) / 2)，
 * dp[i][j] = min{ dp[k][j - 1] + f[k + 1][i] | (j - 1 <= k <= i) }
 * 时间复杂度 O(n^3)
 */

const int MAXN = 500 + 10;

int n, m;
int dp[MAXN][MAXN], f[MAXN][MAXN], dist[MAXN][MAXN], dis[MAXN];

int main() {
    n = getint(); m = getint();
    for (int i = 2; i <= n; ++i) {
        dis[i] = dis[i - 1] + getint();
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            for (int k = i; k <= j; ++k) {
                f[i][j] += std::abs(dis[k] - dis[(i + j) / 2]);
            }
        }
    }
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) dp[i][j] = 0x3f3f3f3f;
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i < j) dp[i][j] = 0;
            else for (int k = j - 1; k <= i; ++k) {
                dp[i][j] = std::min(dp[i][j], dp[k][j - 1] + f[k + 1][i]);
            }
        }
    }
    printf("%d\n", dp[n][m]);
    return 0;
}

