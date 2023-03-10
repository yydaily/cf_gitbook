#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
ll n, m, p;          // n个点，m条边，开始有p钱
ll w[1000];          // 每个点可以赚的钱
ll cost[1000][1000]; // 从a城市到b城市的最小开销
ll id[1000];
pair<ll, ll> ans[1000]; // 到i节点需要的演出数和剩余的钱数
void solve() {
    cin >> n >> m >> p;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            cost[i][j] = INF;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        id[i]         = i;
        ans[i].first  = INF;
        ans[i].second = -INF;
    }
    ans[1].first  = 0;
    ans[1].second = p; // 初始的时候在1城市，表演0次，有钱p
    for (int i = 1, a, b, s; i <= m; i++) {
        cin >> a >> b >> s;
        cost[a][b] = min(cost[a][b], (ll)s);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                cost[j][k] = min(cost[j][k], cost[j][i] + cost[i][k]);
            }
        }
    }
    if (cost[1][n] == INF) { // 如果到达不了，直接输出返回
        cout << -1 << endl;
        return;
    }
    sort(id + 1, id + n + 1, [&](int a, int b) { return w[a] < w[b]; }); // 按照赚钱的数量排序 id
    for (int i = 1; i <= n; i++) {
        int from = id[i]; // 枚举一个不太赚钱的城市
        for (int j = 1; j <= n; j++) {
            if (cost[from][j] == INF)
                continue;
            if (w[j] > w[from] || j == n) {                        // 如果当前城市更赚钱 or 当前城市是最终城市
                ll need_money  = cost[from][j] - ans[from].second; // 飞过去还需要额外赚的钱
                ll display_cnt = 0;                                // 赚这么多钱需要表演的次数
                if (need_money > 0)
                    display_cnt = need_money / w[from] + (need_money % w[from] != 0);
                if (display_cnt + ans[from].first < ans[j].first || (display_cnt + ans[from].first == ans[j].first && ans[from].second - cost[from][j] + w[from] * display_cnt > ans[j].second)) {
                    ans[j].first  = display_cnt + ans[from].first;
                    ans[j].second = ans[from].second - cost[from][j] + w[from] * display_cnt;
                }
            }
        }
    }
    cout << ans[n].first << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
