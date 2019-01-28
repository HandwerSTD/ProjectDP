//
//  4.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/1/28.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <iostream>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;

const int MAXNM = 50 + 10;

int cls[MAXNM][MAXNM];
int n, m, dp[MAXNM][MAXNM][MAXNM][MAXNM];

int main() {
    IMPROVE_IO();
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> cls[i][j];
        }
    }
    for (int x1 = 1; x1 <= m; ++x1) {
        for (int y1 = 1; y1 <= n; ++y1) {
            for (int x2 = 1; x2 <= m; ++x2) {
                for (int y2 = y1 + 1; y2 <= n; ++y2) {
                    dp[x1][y1][x2][y2] = std::max(
                        std::max(
                            dp[x1 - 1][y1][x2 - 1][y2],
                            dp[x1][y1 - 1][x2][y2 - 1]
                        ),
                        std::max(
                            dp[x1 - 1][y1][x2][y2 - 1],
                            dp[x1][y1 - 1][x2 - 1][y2]
                        )
                    );
                    dp[x1][y1][x2][y2] += cls[x1][y1] + cls[x2][y2];
                }
            }
        }
    }
    cout << dp[m][n - 1][m - 1][n] << endl;
    return 0;
}
