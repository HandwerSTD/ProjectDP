//
//  11.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/7/16.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define rep(a,s,t,i) for (int a = s; a <= t; a += i)
#define repp(a,s,t,i) for (int a = s; a < t; a += i)
#define countdown(s) while (s --> 0)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)
#define VISIT(x) ((x % n + 1))

using std::cin;
using std::cout;
using std::endl;

int getint() { int x; scanf("%d", &x); return x; }
long long int getll() { long long int x; scanf("%lld", &x); return x; }

const int MAXN = 100 + 10;

int n, energy[MAXN * 2], dp[MAXN * 2][MAXN * 2];

/**
 *
 * 设 dp[l][r] 表示合并区间[l,r]所带来的最大能量
 * dp[l][r] = Max:
 *     1. dp[l][r] -> 上一次尝试合并获得的能量
 *     2. dp[l][k] + dp[k][r] + energy[l] * energy[k] * energy[r]
 *         -> 任选一珠子 k，分别合并[l,k],[k,r]，再合并[l,r]的能量
 * 注意断环成链
 * 最后答案是在任意位置进行断环成链所获得的答案的最大值
 * 也就是 max{f[i][i + n] | 1 <= i <= n}
 *
 */

int main() {
    n = getint();
    for (int i = 1; i <= n; ++i) {
        energy[i] = getint();
        energy[i + n] = energy[i];
    }
    int N = n * 2;
    for (int siz = 2; siz <= n + 1; ++siz) {
        for (int l = 1; l + siz - 1 <= N; ++l) {
            int r = l + siz - 1;
            for (int k = l + 1; k < r; ++k) {
                dp[l][r] = std::max(dp[l][r], dp[l][k] + dp[k][r] + energy[l] * energy[k] * energy[r]);
            }
        }
    }
    int ans = 0;
    rep (i, 1, n, 1) ans = std::max(ans, dp[i][n + i]);
    printf("%d\n", ans);
    return 0;
}


