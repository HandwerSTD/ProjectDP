//
//  10.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/6/1.
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

/**
 * 贪心做法
 */

short next = 0;
/* 0 -> undefined, 1 -> valley, 2 -> top */
int ans = 1;

int main() {
    IMPROVE_IO();
    int n = 0, lastFlower = 0, nowFlower = 0;
    cin >> n;
    cin >> lastFlower;
    for (int i = 2; i <= n; ++i) {
        cin >> nowFlower;
        if (next == 0) {
            // 正在选第二盆花
            if (lastFlower < nowFlower) {
                next = 1;
                ++ans;
            }
            if (lastFlower > nowFlower) {
                next = 2;
                ++ans;
            }
        } else if (next == 2) {
            // 当前要选波峰
            if (lastFlower < nowFlower) {
                next = 1;
                ++ans;
            }
        } else if (next == 1) {
            // 当前要选波谷
            if (lastFlower > nowFlower) {
                next = 2;
                ++ans;
            }
        }
        lastFlower = nowFlower;
    }
    cout << ans << endl;
    return 0;
}


