//
//  20.cpp
//  ProjectDP
//
//  Created by HandwerSTD on 2019/1/28.
//  Copyright © 2019 Handwer STD. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdio>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;
using std::max;

const int MAXN = 1000000 + 10;

int n, weight[MAXN], sum3, sumtree[MAXN];
std::vector<int> head[MAXN], ans;

void DFS(int u, int father) {
    sumtree[u] = weight[u];
    int amt = head[u].size();
    for (int i = 0; i < amt; ++i) {
        int now = head[u][i];
        if (now == father) continue;
        DFS(now, u);
        sumtree[u] += sumtree[now];
    }
    if (sumtree[u] == sum3) {
        ans.push_back(u);
        sumtree[u] = 0;
    }
}

int main() {
    IMPROVE_IO();
    cin >> n;
    int root = 0, sum = 0;
    for (int i = 1; i <= n; ++i) {
        int next = 0, w = 0;
        cin >> next >> w;
        if (next == 0) root = i;
        else {
            head[i].push_back(next);
            head[next].push_back(i);
        }
        weight[i] = w;
        sum += w;
    }
    if (sum % 3 != 0) {
        cout << "-1" << endl;
        return 0;
    }
    sum3 = sum / 3;
    DFS(root, 0);
    if (ans.size() < 3) {
        cout << -1 << endl;
        return 0;
    }
    cout << ans[0] << ' ' << ans[1] << endl;
    return 0;
}
