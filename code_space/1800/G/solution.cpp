#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
const long long base = 998244353;
const long long mod1 = 1e9 + 7;
const long long mod2 = 1e9 + 9;
const int _          = 2e5 + 10;
int n;
vector<int> edge[_];
struct poi {
    long long val1, val2;
    poi(int _v1 = 0, int _v2 = 0) {
        val1 = _v1;
        val2 = _v2;
    }
    bool operator<(const poi &a) const {
        if (val1 != a.val1)
            return val1 < a.val1;
        return val2 < a.val2;
    }
    bool operator!=(const poi &a) const { return val1 != a.val1 || val2 != a.val2; }
    bool operator==(const poi &a) const { return val1 == a.val1 && val2 == a.val2; }
} val[_];
bool mirror[_];

void dfs(int now, int pre) {
    vector<poi> son_values;
    map<poi, int> cnt;
    val[now].val1 = val[now].val2 = 1;
    for (auto i : edge[now]) {
        if (i == pre)
            continue;
        dfs(i, now);
        son_values.push_back(val[i]);
        cnt[val[i]]++;
    }

    mirror[now] = true;
    auto value  = poi(0, 0);
    for (auto i : cnt) {
        if (i.second % 2 == 0)
            continue;
        value = value != poi(0, 0) ? poi(-1, -1) : i.first;
    }
    if (value == poi(-1, -1)) {
        mirror[now] = false;
    } else if (value != poi(0, 0)) {
        for (auto i : edge[now]) {
            if (i == pre || val[i] != value)
                continue;
            mirror[now] = mirror[i];
        }
    }

    sort(son_values.begin(), son_values.end());
    val[now] = poi(41, 41);
    for (long long i = 0; i < son_values.size(); i++) {
        val[now].val1 = (val[now].val1 + son_values[i].val1 * son_values[i].val1 + son_values[i].val1 * base) % mod1;
        val[now].val2 = (val[now].val2 + son_values[i].val2 * son_values[i].val2 + son_values[i].val2 * base) % mod2;
    }
    // cout<<now<<' '<<val[now]<<endl;
}
void solve() {
    cin >> n;
    for (int i = 1, a, b; i < n; i++) {
        cin >> a >> b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }

    dfs(1, 0);

    cout << (mirror[1] ? "YES" : "NO") << endl;

    // recover
    for (int i = 1; i <= n; i++) {
        edge[i].clear();
        val[i]    = 0;
        mirror[i] = false;
    }
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
