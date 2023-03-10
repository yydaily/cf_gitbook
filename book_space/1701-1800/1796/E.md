## E. Colored Subgraphs

Monocarp has a tree, consisting of $$$n$$$ vertices.

> Monocarp 有一棵树，树包含 $$$n$$$ 个节点。

He is going to select some vertex $$$r$$$ and perform the following operations on each vertex $$$v$$$ from $$$1$$$ to $$$n$$$: 

> 他准备选择一些节点 $$$r$$$ 并对 $$$1$$$ 到 $$$n$$$ 中每个节点 $$$v$$$ 执行下述操作

- set $$$d_v$$$ equal to the distance from $$$v$$$ to $$$r$$$ (the number of edges on the shortest path); 
- color $$$v$$$ some color. 

> 1. 设置 $$$d_v$$$ 等于 $$$v$$$ 到 $$$r$$$ 的距离（也即最短路上的边数）
> 2. 给 $$$v$$$ 一个颜色

A *nice* coloring satisfies two conditions: 

> 一个 *好的* 染色需要满足两个条件：

- for each pair of vertices of the same color $$$(v, u)$$$, there exists a path from $$$v$$$ to $$$u$$$ that only visits vertices of the same color; 
- for each pair of vertices of the same color $$$(v, u)$$$, $$$d_v \neq d_u$$$. 

> 1. 对于任何相同颜色的节点对 $$$(v, u)$$$，存在一条从 $$$v$$$ 到 $$$u$$$ 的路径且路径上所有的点同色。
> 2. 对于任何相同颜色的节点对 $$$(v, u)$$$，$$$d_v \neq d_u$$$。

Note that Monocarp can choose any amount of different colors he wants to use.

> 注意，Monocarp可以选择任意数量的不同颜色。

For each used color, he then counts the number of vertices of this color. The *cost* of the tree is the minimum of these numbers.

> 对于每个用到的颜色，它会统计这个颜色对应的节点数。这棵树的花费是这些节点数的最小值。

What can be the maximum cost of the tree?

> 你能统计出树的最大花费吗？

### Input

The first line contains a single integer $$$t$$$ ($$$1 \le t \le 10^4$$$) — the number of testcases.

> 第一行包含一个整数$$$t$$$ ($$$1 \le t \le 10^4$$$) —— 表示测试用例数。

The first line of each testcase contains a single integer $$$n$$$ ($$$3 \le n \le 2 \cdot 10^5$$$) — the number of vertices in the tree.

> 每个测试用例的第一行包含一个整数 $$$n$$$ ($$$3 \le n \le 2 \cdot 10^5$$$) —— 表示树中节点数的数量。

Each of the next $$$n-1$$$ lines contains two integers $$$v$$$ and $$$u$$$ ($$$1 \le v, u \le n$$$) — the description of an edge.

> 接下来 $$$n-1$$$ 行，每行包含两个整数$$$v$$$ and $$$u$$$ ($$$1 \le v, u \le n$$$) —— 表示树上的边。

The given edges form a tree. The sum of $$$n$$$ over all testcases doesn't exceed $$$2 \cdot 10^5$$$.

> 这些给定的边会构成一棵树，保证所有测试用例的 $$$n$$$ 求和不会超过 $$$2 \cdot 10^5$$$。

### Output

For each testcase print a single integer — the maximum possible cost of the tree.

> 对于每个测试用例输出一个整数 —— 表示树的最大花费。

### 题解

题目描述花里胡哨，看了半天才明白染色的意义。

由于对于任何相同颜色的节点对 $$$(v, u)$$$，$$$d_v \neq d_u$$$，所以对于同一种颜色来说，他们相对于根的距离肯定不同，又由于对于任何相同颜色的节点对 $$$(v, u)$$$，存在一条从 $$$v$$$ 到 $$$u$$$ 的路径且路径上所有的点同色，所以同色的一定是一条从叶指向根的一条路径（可能不包含叶、根）

那么问题就转换成了，如何将树删掉一些边，转换成多个单链，让拆分后的最短单链长度最长。

不难发现，这里的拆分是满足二分条件的，所以考虑二分。假设当前二分的值是 $$$mid$$$，我们只需要判断这个值是否是合理的。

显然，对于所有的叶节点必须要满足存在一条指向根长度为 $$$mid$$$ 的路径。所以一个贪心的策略就是，每个根节点都会向上走 $$$mid$$$ 步，然后染色，如果某个叶节点不存在没染色的长度为 $$$mid$$$ 的路径，就说明这种长度是不存在解的。反之亦然。

如此，可以二分+DFS可解，复杂度是 $$$O(n*log(n))$$$

但是上述的考虑都是基于根节点只有一个而且固定，但是按照题意，所有的节点都可以是根节点，如果我们每次都重新跑一次二分+DFS，总复杂度就会退化成 $$$O(n^2*log(n))$$$，这显然是不可接受的。

不妨考虑，基于第一次DFS可以得到哪些信息？首先我们能得到每个节点的被哪个叶节点占用，到叶节点的距离，有多少个子节点到叶节点长度不足 $$$mid$$$。然后我们考虑换根对这些数据的影响，假设换根的节点是节点 $$$u$$$ 和节点 $$$v$$$，那么显然由于根的转换，$$$u$$$ 到 $$$v$$$ 路径上所有节点的这些信息都将被替换，而除此之外的节点，你可以想象成 $$$u$$$ 到 $$$v$$$ 的路径缩成了一个点，那么其他节点是不会影响的（因为缩点后，从这些节点的视角出发，根是没变的）。也就是说，我们每次换根并不需要重新跑一次完整的DFS，而是只需要更新 $$$u$$$ 到 $$$v$$$ 的路径上的数据就可以了。

既然如此，我们不妨让 $$$u$$$ 和 $$$v$$$ 有父子关系，这样每次换根的成本可以进一步降低——即每次只需要更新两个节点。

基于这个想法，显然我们可以通过重跑一次DFS来将所有的节点标记为根并统计答案。

### 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int _ = 2e5 + 10;
int n, ans;
vector<int> v[_];
int dis[_]; // 叶节点到当前节点的距离
int cnt[_]; // 有多少个子节点不满足dis >= ans
int num[_]; // 对cnt的聚合，用于快速判断
bool dfs1(int now, int pre) {
    dis[now] = 1e9;
    for (auto i : v[now]) {
        if (i == pre)
            continue;
        dfs1(i, now);
        if (dis[i] < ans) {
            cnt[now]++;
        }
        dis[now] = min(dis[now], dis[i] + 1); // 这里默认选择路径最短的子树，这样对贡献才有意义
    }
    if (dis[now] == 1e9)
        dis[now] = 1; // 对于叶节点单独处理
    num[cnt[now]]++;
    return num[0] + num[1] == n && dis[now] >= ans; // 如果不存在多个子树不满足，并且根节点满足条件，说明子树满足条件
}
// 换根操作
void reroot(int old_root, int new_root) {
    // dis 和 cnt 需要重新计算，并且需要更新 num
    num[cnt[old_root]]--;
    num[cnt[new_root]]--;
    if (dis[new_root] < ans)
        cnt[old_root]--;                      // 如果新根的dis较小，说明之前统计老根的cnt的时候多统计了一个
    if (dis[old_root] == dis[new_root] + 1) { // 这里说明新根是指向老根的
        bool exist_ano_son = false;           // 判断是否存在多个老根的子节点距离相同，如果有多个，说明老根的dis不需要更新
        int new_dis        = 1e9;
        for (auto i : v[old_root]) {
            if (i == new_root)
                continue;
            new_dis = min(new_dis, dis[i] + 1);
            if (dis[i] + 1 == dis[old_root]) {
                exist_ano_son = true;
                break;
            }
        }
        if (new_dis == 1e9)
            new_dis = 1;
        if (!exist_ano_son) {
            dis[old_root] = new_dis;
        }
    }
    if (dis[new_root] == 1)
        dis[new_root] = dis[old_root] + 1; // 说明之前是叶节点，这种情况需要额外更新新根的dis
    dis[new_root] = min(dis[new_root], dis[old_root] + 1);
    if (dis[old_root] < ans)
        cnt[new_root]++;

    num[cnt[old_root]]++;
    num[cnt[new_root]]++;
}
bool dfs2(int now, int pre) {
    bool ret = false;
    if (now != 1) {
        reroot(pre, now); // 换根操作
        if (num[0] + num[1] == n && dis[now] >= ans)
            ret = true; // 换根后判断答案
    }
    for (auto i : v[now]) {
        if (i == pre)
            continue;
        if (dfs2(i, now))
            ret = true; // 这里并不能直接return，因为是二分的，所以要跑多次，必须将根回滚到1节点
    }
    if (now != 1) {
        reroot(now, pre); // 根回滚
    }
    return ret;
}
bool check(int buf) {
    ans = buf;
    for (int i = 0; i <= n; i++)
        dis[i] = cnt[i] = num[i] = 0;

    return dfs1(1, 0) || dfs2(1, 0);
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        v[i].clear();
    for (int i = 1, a, b; i < n; i++) {
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    int l = 1, r = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }
    cout << r << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```
