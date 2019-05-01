//
//  22.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/4/20.
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

const int MAXN = 1500 + 10;

int n, dp[MAXN][3], value[MAXN], ind[MAXN];
std::vector<int> G[MAXN];

/**
 *
 * dp[root][0]: 让节点 root 的父亲来覆盖节点 root
 * dp[root][1]: 让节点 root 自己覆盖自己
 * dp[root][2]: 让节点 root 的儿子来覆盖节点 root
 *
 */

inline void addEdge(int prev, int next) {
    G[prev].push_back(next);
    G[next].push_back(prev);
    ++ind[next];
}

void DFS(int root = 1, int father = 0) {
    dp[root][1] = value[root];
    bool tr = true;
    int minCost = 0x7f7f7f7f;
    for (auto v : G[root]) {
        // C++11 FEATURE
        // DON'T FORGET TO TURN ON C++11
        if (v == father) continue;
        DFS(v, root);
        
        dp[root][0] += std::min(dp[v][1], dp[v][2]);
        // 当 root 被自己的父亲覆盖时，root 的儿子必须自己完成覆盖：它自己覆盖自己，或者让 root 的孙子覆盖 root 的儿子
        
        dp[root][1] += std::min(dp[v][0], std::min(dp[v][1], dp[v][2]));
        // 当 root 能覆盖自己时，它的儿子怎么覆盖显然已经不重要了，挑一个最小的加上即可
        
        dp[root][2] += std::min(dp[v][1], dp[v][2]);
        // 当 root 被自己的儿子覆盖时，root 的儿子必须要合法，选择同 dp[root][0]
        if (dp[v][1] < dp[v][2]) tr = false; // 选择 root 的儿子比选择 root 的孙子要更优，记录一下
        else minCost = std::min(minCost, dp[v][1] - dp[v][2]); // 记一下「差值」
    }
    if (tr) dp[root][2] += minCost;
    // 如果一个 dp[root][1] 都没选过，就从「差值」最小的儿子里选一个
}

int main() {
    IMPROVE_IO();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int id = 0, w = 0, k = 0;
        cin >> id >> w >> k;
        value[id] = w;
        for (int i = 1; i <= k; ++i) {
            int qwq = 0;
            cin >> qwq;
            addEdge(id, qwq);
        }
    }
    int root = 0;
    for (int i = 1; i <= n; ++i) {
        if (ind[i] == 0) {
            root = i;
            break;
        }
    }
    DFS(root, 0);
    cout << std::min(dp[root][1], dp[root][2]) << endl;
    return 0;
}

