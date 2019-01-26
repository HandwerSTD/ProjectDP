//
//  1.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/1/24.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>

const int MAXR = 1000 + 10;

int T[MAXR][MAXR], r, mem[MAXR][MAXR], dp[MAXR][MAXR];

int Basic_Search(int x, int y) {
    if (x == r) return T[x][y];
    return std::max(Basic_Search(x + 1, y), Basic_Search(x + 1, y + 1)) + T[x][y];
}

int Search(int x, int y) {
    if (x == r) return T[x][y];
    if (mem[x + 1][y] == -1) mem[x + 1][y] = Search(x + 1, y);
    if (mem[x + 1][y + 1] == -1) mem[x + 1][y + 1] = Search(x + 1, y + 1);
    return std::max(mem[x + 1][y], mem[x + 1][y + 1]) + T[x][y];
}

int DP() {
    for (int i = r - 1; i >= 1; --i) {
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = std::max(dp[i + 1][j], dp[i + 1][j + 1]) + T[i][j];
        }
    }
    return dp[1][1];
}

int main(int argc, const char * argv[]) {
    scanf("%d", &r);
    memset(mem, -1, sizeof mem);
    for (int i = 1; i <= r; ++i) {
        for (int x = 1; x <= i; ++x) {
            scanf("%d", &T[i][x]);
            dp[i][x] = T[i][x]; // Special for DP
        }
    }
    //printf("%d\n", Search(1, 1));
    printf("%d\n", DP()); // Special for DP
    return 0;
}
