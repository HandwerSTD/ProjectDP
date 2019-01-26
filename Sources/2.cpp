//
//  2.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/1/25.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <iostream>
#include <cstdio>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;

const int MAXN = 100000 + 10;

int n, a[MAXN], dp[MAXN];

/*
 *
 * dp[i] records the longest sequence that not after i
 * Formula:
 *     dp[i] = max { dp[j] } + 1 (1 <= j <= i - 1), (a[i] >= a[j])
 * Answer:
 *     max { dp[i] } (1 <= i <= n)
 *
 */

int ans = 0;

int main() {
    IMPROVE_IO();
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        int max = 0;
        for (int j = 1; j <= i - 1; ++j) {
            if (a[i] >= a[j]) max = std::max(max, dp[j]);
        }
        dp[i] = max + 1;
        ans = std::max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}
