//
//  26.cpp
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

const int MAXLENGTH = 8 + 4;

/*
 *
 * dp[i][j]: length = i, the start number = j
 *
 */

int dp[MAXLENGTH][MAXLENGTH];
int n, m;

void Init() {
    dp[0][0] = 1;
    for (int i = 1; i <= 9; ++i) {
        // enumeration length
        for (int j = 0; j <= 9; ++j) {
            if (j == 4) dp[i][j] = 0;
            else {
                for (int k = 0; k <= 9; ++k) {
                    dp[i][j] += dp[i - 1][k];
                }
                if (j == 6) dp[i][j] -= dp[i - 1][2];
            }
        }
    }
}

int Solve(int x) {
    // returns the amount in [0, x)
    int ans = 0;
    int num[MAXLENGTH] = {0};
    // num[0] <=> cnt
    while (x) {
        num[++num[0]] = x % 10;
        x /= 10;
    }
    for (int i = num[0]; i >= 1; --i) {
        for (int j = 0; j < num[i]; ++j) {
            if (j == 4 || (num[i + 1] == 6 && j == 2)) continue;
            ans += dp[i][j];
        }
        if (num[i] == 4) break;
        if (num[i + 1] == 6 && num[i] == 2) break;
    }
    return ans;
}

int main() {
    IMPROVE_IO();
    Init();
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        cout << Solve((m) + 1) - Solve((n - 1) + 1) << endl;
    }
    return 0;
}
