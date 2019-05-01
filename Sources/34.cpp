//
//  34.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/5/1.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <iostream>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;

const int MAXN = 16 + 5;
const int FIXED_N = (1 << 16) - 1 + 10;

int w, n;

struct P {
    int w, t;
    
    P() : w(0), t(0) {}
    P(int w, int t) : w(w), t(t) {}
} p[MAXN];

int dp[FIXED_N];
int statTime[FIXED_N], statWeight[FIXED_N];
// statTime[stat]: 状态为 stat 的总时间
// statWeight[stat]: 同理，重量

int main() {
    IMPROVE_IO();
    cin >> w >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].t >> p[i].w;
    }
    for (int stat = 1; stat <= ((1 << n) - 1); ++stat) {
        // 没必要从 0 开始枚举，连第二层循环都进不去
        for (int pass = 1; pass <= n; ++pass) {
            // 第 pass 个过桥的人
            int now = pass - 1;
            if (stat & (1 << now)) {
                statTime[stat] = std::max(statTime[stat], p[pass].t);
                statWeight[stat] += p[pass].w;
            }
        }
        if (statWeight[stat] > w) dp[stat] = 0x7f7f7f7f; // 超出重量没法选
        else dp[stat] = statTime[stat];
    }
    for (int stat = 1; stat <= ((1 << n) - 1); ++stat) {
        for (int s0 = stat; s0; s0 = (s0 - 1) & stat) {
            // s0 为 stat 的一个子集
            dp[stat] = std::min(dp[stat], dp[stat ^ s0]/* 原状态不选 s0 */ + dp[s0] /* 新状态选 s0 */);
        }
    }
    cout << dp[((1 << n) - 1)] << endl;
    return 0;
}

