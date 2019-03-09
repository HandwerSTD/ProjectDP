//
//  28.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/1/29.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <iostream>
#include <vector>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)
#define Stat(__x) FIXED_STATUS[__x]

using std::cin;
using std::cout;
using std::endl;

const int MAXSTATUS = (1 << 12) - 1 + 10;
const int MAXMN = 12 + 5;
const int HA = 100000000;

int m, n;
int farm[MAXMN][MAXMN];
int dp[MAXMN][MAXSTATUS], FIXED_STATUS[MAXSTATUS];

/*
 *
 * dp[i][stat]: line = i, status = stat (binary)
 *
 */

int main() {
    IMPROVE_IO();
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> farm[i][j];
            Stat(i) = (Stat(i) << 1) + farm[i][j];
        }
    }
    
    dp[0][0] = 1;
    for (int i = 1; i <= m; ++i) {
        for (int status = 0; status <= (1 << n) - 1; ++status) {
            if ((status & (status << 1)) != 0) continue;
            // some grass are close to each other
            if ((status & Stat(i)) != status) continue;
            // at least one grass planted on a barren place
            for (int pre_stat = 0; pre_stat <= (1 << n) - 1; ++pre_stat) {
                if ((status & pre_stat) == 0) {
                    dp[i][status] += dp[i - 1][pre_stat];
                    dp[i][status] %= HA;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= (1 << n) - 1; ++i) {
        ans += dp[m][i];
        ans %= HA;
    }
    cout << ans << endl;
    return 0;
}
