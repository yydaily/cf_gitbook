#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
int n;
int d[1024];
void solve() {
    cin >> n;
    int sub_cnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        if (d[i] < 0)
            sub_cnt++;
    }

    sort(d, d + n);
    map<int, bool> m;
    for (int i = n - 1; i >= 0 && d[i] > 0; i--) {
        if (m[d[i]])
            continue;
        m[d[i]] = true;
        cout << m.size() << ' ';
    }
    int add = n - m.size() - sub_cnt;
    for (int i = 1; i <= add; i++)
        cout << m.size() - 1 << ' ' << m.size() << ' ';
    for (int i = 1; i <= sub_cnt - add; i++)
        cout << m.size() - i << ' ';
    cout << endl;

    for (int i = 1; i <= sub_cnt; i++)
        cout << 1 << ' ' << 0 << ' ';
    for (int i = 2 * sub_cnt + 1; i <= n; i++)
        cout << i - 2 * sub_cnt << ' ';
    cout << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
