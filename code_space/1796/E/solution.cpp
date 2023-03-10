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
