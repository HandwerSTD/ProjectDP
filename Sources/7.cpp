//
//  7.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/3/9.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <algorithm>
#include <iostream>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;

const int MAXN = 150000 + 10;

struct Segment {
    int l, r;
    
    Segment() { l = r = 0; }
    bool operator < (const Segment &that) const {
        if (r == that.r) return l < that.l;
        return r < that.r;
    }
} seg[MAXN];

int n, dp[MAXN];

int BinarySearch(int x) {
    int l = 1, r = x, ans = -2147482333;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (seg[mid].r < seg[x].l) {
            l = mid + 1;
            ans = mid;
        } else r = mid - 1;
    }
    return ans;
}

int main() {
    IMPROVE_IO();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> seg[i].l >> seg[i].r;
    }
    std::sort(seg + 1, seg + 1 + n);
    for (int i = 1; i <= n; ++i) {
        int pre = BinarySearch(i);
        if (pre == -2147482333) dp[i] = std::max(dp[i - 1], seg[i].r - seg[i].l + 1);
        else dp[i] = std::max(dp[i - 1], dp[pre] + seg[i].r - seg[i].l + 1);
    }
    cout << dp[n] << endl;
    return 0;
}

