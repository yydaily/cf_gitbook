#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
const int _ = 5e5 + 10;
int n;
int a[_], b[_];
struct poi {
    int value;
    int is_a;
    int index;
    poi(int _v = 0, int _is = 0, int _ind = 0) {
        value = _v;
        is_a  = _is;
        index = _ind;
    }
    bool operator<(const poi &a) const {
        if (value != a.value)
            return value < a.value;
        if (index != a.index)
            return index < a.index;
        return is_a < a.is_a;
    }
};
int handle(poi &x, multiset<int> &a0, multiset<int> &b0) {
    int ans = 2e9 + 10;
    if (x.is_a) {
        if (b[x.index] <= x.value)
            b0.erase(b0.find(b[x.index]));

        if (b0.size() > 0) {
            auto it = b0.upper_bound(x.value);
            it--;
            ans = min(ans, (x.value - *it));
        }

        if (b[x.index] <= x.value)
            b0.insert(b[x.index]);
    } else {
        if (a[x.index] <= x.value)
            a0.erase(a0.find(a[x.index]));

        if (a0.size() > 0) {
            auto it = a0.upper_bound(x.value);
            it--;
            ans = min(ans, (x.value - *it));
        }

        if (a[x.index] <= x.value)
            a0.insert(a[x.index]);
    }
    return ans;
}
void solve() {
    cin >> n;
    vector<poi> v;
    int x = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        v.push_back(poi(a[i], 1, i));
        v.push_back(poi(b[i], 0, i));
        x = max(x, min(a[i], b[i]));
    }
    sort(v.begin(), v.end());

    int ans = 2e9 + 10;
    multiset<int> a0, b0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].is_a) {
            a0.insert(v[i].value);
            // cout<<"a add "<<v[i].value<<endl;
        } else {
            b0.insert(v[i].value);
            // cout<<"b add "<<v[i].value<<endl;
        }
        if (v[i].value < x)
            continue;
        if (i < v.size() - 1 && v[i].value == v[i + 1].value)
            continue;
        if (a0.size() == 0 || b0.size() == 0)
            continue;
        int buf_index = i;
        while (buf_index > 0 && v[buf_index].value == v[i].value) {
            ans = min(ans, handle(v[buf_index], a0, b0));
            buf_index--;
        }
    }
    cout << ans << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
