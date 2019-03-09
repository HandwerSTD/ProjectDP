//
//  16.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/2/16.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <iostream>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;

const int dx[] = { 0,  0, -1,  1 };
const int dy[] = { 1, -1,  0,  0 };
const int MAXRC = 100 + 10;

int snow[MAXRC][MAXRC];
int r, c, ans;
int mem[MAXRC][MAXRC];

int Search(int x, int y) {
    int t = 1;
    if (mem[x][y]) t = mem[x][y];
    else {
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx > 0 && ny > 0 && nx <= r && ny <= c && snow[x][y] < snow[nx][ny]) {
                t = std::max(t, Search(nx, ny) + 1);
            }
        }
    }
    mem[x][y] = t;
    return t;
}

int main() {
    IMPROVE_IO();
    cin >> r >> c;
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> snow[i][j];
        }
    }
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            int now = Search(i, j);
            mem[i][j] = now;
            ans = std::max(ans, mem[i][j]);
        }
    }
    cout << ans << endl;
    return 0;
}


