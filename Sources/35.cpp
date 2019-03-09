//
//  35.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/2/16.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

const int MAXN = 100000 + 10;

std::vector<int> head[MAXN];
int flower[MAXN], dp[MAXN], n, id[MAXN], ans;

/*
 *
 * dp[u] += std::max(0, dp[v]);
 *
 */

void DFS(int u, int fa) {
    dp[u] = flower[u];
    for (std::vector<int>::iterator it = head[u].begin(); it != head[u].end(); it++) {
        if ((*it) == fa) continue;
        DFS((*it), u);
        dp[u] += std::max(0, dp[(*it)]);
    }
    ans = std::max(ans, dp[u]);
}

int main(int argc, const char * argv[]) {
    std::ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> flower[i];
    for (int i = 1; i <= n - 1; ++i) {
        int prev = 0, next = 0;
        cin >> prev >> next;
        if (prev > next) std::swap(prev, next);
        head[prev].push_back(next);
        head[next].push_back(prev);
        ++id[next];
    }
    int root = 0;
    for (root = 1; root <= n; ++root)
        if (id[root] == 0) break;
    DFS(root, 0);
    cout << ans << endl;
    return 0;
}

