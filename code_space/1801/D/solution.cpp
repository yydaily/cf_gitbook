#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
ll n, m, p; // n个点，m条边，开始有p钱
ll w[1000]; // 每个点可以赚的钱
ll cost[1000][1000];
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
    ans[1].first  = 0; // 1节点初始化
    ans[1].second = p;
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

    if (cost[1][n] == INF) { // 如果不可达直接返回
        cout << -1 << endl;
        return;
    }
    sort(id + 1, id + n + 1, [&](int a, int b) { return w[a] < w[b]; });
    for (int i = 1; i <= n; i++) { // 枚举一个不太赚钱的城市
        int from = id[i];
        for (int j = 1; j <= n; j++) {
            if (cost[from][j] == INF)
                continue;
            if (w[j] > w[from] || j == n) {                        // 找到一个更赚钱的城市
                ll need_money  = cost[from][j] - ans[from].second; // 计算需要赚的钱
                ll display_cnt = 0;                                // 计算需要表演的次数
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
