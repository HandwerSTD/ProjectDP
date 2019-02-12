//
//  8.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/1/28.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <iostream>
#include <vector>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;

const int MAXN = 6000 + 10;

/*
 *
 * dp[u][true]: Choose Node[u]
 * dp[u][false]: Don't choose Node[u]
 *
 */

int val[MAXN], n;
int dp[MAXN][2], inDegree[MAXN];
std::vector<int> head[MAXN];

void DFS(int u) {
    dp[u][0] = 0;
    dp[u][1] = val[u];
    int siz = (int) head[u].size();
    for (int i = 0; i < siz; ++i) {
        int v = head[u][i];
        DFS(v);
        dp[u][1] += dp[v][0];
        dp[u][0] += std::max(dp[v][0], dp[v][1]);
    }
}

int main() {
    IMPROVE_IO();
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> val[i];
    int maxNode = -1, minNode = MAXN + 1000;
    for (int i = 1; i <= n - 1; ++i) {
        int father = 0, child = 0;
        cin >> child >> father;
        head[father].push_back(child);
        ++inDegree[child];
        maxNode = std::max(maxNode, std::max(father, child));
        minNode = std::min(minNode, std::min(father, child));
    }
    int root = 0;
    for (int i = minNode; i <= maxNode; ++i) {
        if (inDegree[i] == false) root = i;
        if (root != 0) break;
    }
    DFS(root);
    cout << std::max(dp[root][0], dp[root][1]) << endl;
    return 0;
}

