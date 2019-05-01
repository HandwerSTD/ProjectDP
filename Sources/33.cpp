//
//  33.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/3/9.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;

const int MAXN = 10000 + 10 ;

int qwq[5 + 5], grps[MAXN][5 + 5], dp[(1 << 5) - 1 + 10] ;
int n, k;

int Search(int s, int sum) {
    if (sum == 0) return 0;
    int tmp = 0 ;
    for (int s0 = s; s0; s0 = s & (s0 - 1))
        tmp = std::max(tmp, dp[s0] + Search ((s0 ^ s), sum - 1));
    return tmp;
}

int main() {
    IMPROVE_IO();
    int T = 0;
    cin >> T;
    while (T --> 0) {
        memset(qwq, 0, sizeof qwq);
        cin >> n >> k;
        for (int i = 1 ; i <= n; ++i)
            for (int j = 0; j < 5; ++j){
                cin >> grps[i][j];
                qwq[j] = std::max(qwq[j], grps[i][j]) ;
            }
        if (k >= 5) {
            int ans = 0;
            for (int i = 0 ; i < 5 ; ++i) ans += qwq[i] ;
            cout << ans << endl;
        } else {
            memset(dp, 0, sizeof (dp)) ;
            for (int i = 1; i <= n; ++i) {
                for (int stat = 0; stat <= (1 << 5) - 1; ++stat) {
                    int tmp = 0;
                    for (int sel = 0; sel < 5; ++sel) {
                        if (stat & (1 << sel)) tmp += grps[i][sel];
                    }
                    dp[stat] = std::max(dp[stat], tmp);
                }
            }
            cout << Search((1 << 5) - 1, k) << endl;
        }
    }
    return 0 ;
}
