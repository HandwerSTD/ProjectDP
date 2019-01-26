//
//  main.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/1/24.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

/*
 *
 * A file for coding & debugging
 *
 */

#include <iostream>
#include <cstdio>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;
using std::max;

/*
 *
 * CARD1 means the card that can make the turtle go 1 block.
 * CARD2, CARD3 and CARD4 too.
 * dp[i][j][k][l] records the max score when there are i CARD1(s), j CARD2(s), k CARD3(s) and l CARD4(s) have been used.
 *
 * Formula:
 *     Max = dp[i][j][k][k]
 *     Max = max(Max, dp[i-1][j][k][l]) (i >= 1)
 *     Max = max(Max, dp[i][j-1][k][l]) (j >= 1)
 *     Max = max(Max, dp[i][j][k-1][l]) (k >= 1)
 *     Max = max(Max, dp[i][j][k][l-1]) (l >= 1)
 *     dp[i][j][k][l] = Max
 *
 * Answer:
 *     dp[a][b][c][d],
 *     a -> the amount of CARD1, b, c, and d too.
 *
 */

const int MAXN = 350 + 10;
const int MAXM = 120 + 10;
const int MAXCARD =  10;

int n, m, sc[MAXN], cds[MAXM];
int a, b, c, d;
int dp[MAXCARD][MAXCARD][MAXCARD][MAXCARD];

int main() {
    IMPROVE_IO();
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> sc[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> cds[i];
        if (cds[i] == 1) ++a;
        if (cds[i] == 2) ++b;
        if (cds[i] == 3) ++c;
        if (cds[i] == 4) ++d;
    }
    dp[0][0][0][0] = sc[1];
    for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) {
            for (int k = 0; k <= c; ++k) {
                for (int l = 0; l <= d; ++l) {
                    int walked = 1 + i * 1 + j * 2 + k * 3 + l * 4;
                    if (walked > n) break;
                    int Max = dp[i][j][k][l];
                    if (i - 1 >= 0) Max = max(Max, dp[i-1][j][k][l]);
                    if (j - 1 >= 0) Max = max(Max, dp[i][j-1][k][l]);
                    if (k - 1 >= 0) Max = max(Max, dp[i][j][k-1][l]);
                    if (l - 1 >= 0) Max = max(Max, dp[i][j][k][l-1]);
                    dp[i][j][k][l] = Max;
                }
            }
        }
    }
    cout << dp[a][b][c][d] << endl;
    return 0;
}
