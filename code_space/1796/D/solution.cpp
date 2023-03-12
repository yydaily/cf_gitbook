#include <iostream>
using namespace std;
typedef long long ll;
const ll _ = 2e5 + 10;
ll n, k, x;
ll d[_];
ll l[_];
ll sum[_];
ll sum_suf[_];
ll ans;
ll cal() {
    sum[0] = l[0] = 0;
    ll ret        = 0;
    for (int i = 1; i <= n; i++) {
        if (sum[i - 1] >= 0) {
            sum[i] = sum[i - 1] + d[i];
            l[i]   = l[i - 1];
        } else {
            sum[i] = d[i];
            l[i]   = i;
        }
        ret = max(ret, sum[i]);
    }
    sum_suf[n]     = max(0LL, d[n]);
    sum_suf[n + 1] = 0;
    for (int i = n - 1; i >= 1; i--) {
        sum_suf[i] = max(0LL, sum_suf[i + 1] + d[i]);
    }
    return ret;
}
void solve1() {
    ll ans = 0;
    for (int i = 1; i <= k; i++)
        d[i] += x;
    ans = cal();
    for (int i = k; i >= 1; i--) {
        d[i] -= x;
        d[n + i - k] += x;
        ans = max(ans, cal());
    }
    cout << ans << endl;
}
void solve2() {
    cal();
    for (int i = 1; i <= n; i++) {
        ll now = 0;
        for (int j = 0; j < k && i + j <= n; j++) {
            now += d[i + j] + x;
            ans = max(ans, now + sum_suf[i + j + 1]);
        }
    }
    cout << ans << endl;
}
void solve() {
    cin >> n >> k >> x;
    ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
        d[i] -= x;
    }
    if (x * k == 0) {
        cout << cal() << endl;
        return;
    }
    x *= 2;
    if (x < 0)
        solve1();
    else
        solve2();
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
