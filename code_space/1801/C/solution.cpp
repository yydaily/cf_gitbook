#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
void input(vector<int> &ret) {
    ret.clear();
    int len, buf;
    cin >> len;
    while (len--) {
        cin >> buf;
        if (ret.size() == 0 || buf > ret[ret.size() - 1])
            ret.push_back(buf);
    }
}
const int _ = 2e5 + 10;
vector<int> vs[_];
bool cmp(const vector<int> &a, const vector<int> &b) { return a[a.size() - 1] < b[b.size() - 1]; }
struct poi {
    int val;
    int len;
    poi(int _v = 0, int _l = 0) {
        val = _v;
        len = _l;
    }
    bool operator<(const poi &a) const {
        if (val != a.val)
            return val < a.val;
        return len < a.len;
    }
};
void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        input(vs[i]);
    sort(vs, vs + n, cmp);
    set<poi> s;
    s.insert(poi(0, 0));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int buf = 0;
        for (int j = 0; j < vs[i].size(); j++) {
            auto x = s.lower_bound(poi(vs[i][j], 0));
            x--;
            buf = max(buf, (*x).len + int(vs[i].size()) - j);
        }
        s.insert(poi(vs[i][vs[i].size() - 1], buf));
        ans = max(ans, buf);
    }
    cout << ans << endl;
}
int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
