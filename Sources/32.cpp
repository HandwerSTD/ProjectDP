//
//  32.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/5/1.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;

const int FIXED_LENGTH = (1 << 16) - 1 + 10;

std::string s;
bool statPal[FIXED_LENGTH];
int dp[FIXED_LENGTH], len;

void Clear() {
    memset(statPal, false, sizeof statPal);
    memset(dp, 0x7f, sizeof dp);
    dp[0] = 0;
}
void Read() {
    cin >> s;
}
bool isPal(int stat) {
    int l = 0, r = len - 1;
    while (l < r) {
        while ((stat & (1 << r)) == 0) --r;
        while ((stat & (1 << l)) == 0) ++l;
        if (s[l] != s[r]) return false;
        ++l; --r;
    }
    return true;
}
void Process() {
    len = (int) s.length();
    for (int stat = 1; stat <= ((1 << len) - 1); ++stat) {
        // 没必要从 0 开始枚举
        statPal[stat] = isPal(stat);
    }
    for (int stat = 0; stat <= ((1 << len) - 1); ++stat) {
        for (int s0 = stat; s0; s0 = (s0 - 1) & stat) {
            if (statPal[s0]) {
                dp[stat] = std::min(dp[stat], dp[stat - s0] /* 去掉 s0 */ + 1 /* 步数 + 1 */);
            }
        }
    }
}
void Print() {
    cout << dp[((1 << len) - 1)] << endl;
}

int main() {
    IMPROVE_IO();
    int __T = 0;
    cin >> __T;
    while (__T --> 0) {
        Clear();
        Read();
        Process();
        Print();
    }
    return 0;
}


