//
//  27.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/1/29.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>

#define IMPIO() std::ios::sync_with_stdio(false);
#define FILE_IN(__file) freopen(__file, 'r', stdin);
#define FILE_OUT(__file) freopen(__file, 'w', stdout);

using std::cin;
using std::cout;
using std::endl;

const int MAXN = 9 + 2;
const int MAXK = MAXN * MAXN;

int n, k;
int stats[(1 << MAXN) - 1 + 10], popc[(1 << MAXN) - 1 + 10], cnt;
long long int dp[MAXN][(1 << MAXN) - 1 + 10][MAXK];

/*
 *
 * dp[i][stat][k]: line i, status stat, k kings
 *
 */

int Popcount(int x) {
    int ret = 0;
    while (x) {
        if (x & 1) ++ret;
        x >>= 1;
    }
    return ret;
}

bool CheckFailed(int stat1, int stat2) {
    if ((stat1 & stat2) != 0) return true;
    if ((stat1 & (stat2 << 1)) != 0) return true;
    if (((stat1 << 1) & stat2) != 0) return true;
    return false;
}

int main() {
    IMPIO();
    cin >> n >> k;
    for (int i = 0; i <= (1 << n) - 1; ++i) {
        if ((i & (i << 1)) != 0) continue;
        stats[++cnt] = i;
        dp[1][cnt][Popcount(i)] = 1;
    }
    
    for (int i = 2; i <= n; ++i) {
        for (int idj = 1; idj <= cnt; ++idj) {
            for (int idk = 1; idk <= cnt; ++idk) {
                if (CheckFailed(stats[idj], stats[idk])) continue;
                for (int l = 0; l <= k; ++l) {
                    dp[i][idj][Popcount(stats[idj]) + l]
                    += dp[i - 1][idk][l];
                }
            }
        }
    }
    
    long long int ans = 0;
    for (int i = 1; i <= cnt; ++i) {
        ans += dp[n][i][k];
    }
    cout << ans << endl;
    return 0;
}
