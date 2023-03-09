#include <cstring>
#include <iostream>
using namespace std;
int n, k;
string a, b;
int cnt[26];
bool check(int l, int r, int l2 = 0, int r2 = -1) {
    memset(cnt, 0, sizeof(cnt));
    for (int i = l; i <= r; i++) {
        cnt[int(a[i] - 'a')]++;
        cnt[int(b[i] - 'a')]--;
    }
    for (int i = l2; i <= r2; i++) {
        cnt[int(a[i] - 'a')]++;
        cnt[int(b[i] - 'a')]--;
    }
    for (int i = 0; i < 26; i++) {
        if (cnt[i] != 0) {
            cout << "NO" << endl;
            return false;
        }
    }
    return true;
}
void solve() {
    cin >> n >> k >> a >> b;
    if (a.length() != b.length()) {
        cout << "NO" << endl;
        return;
    }
    if (!check(0, n - 1))
        return;

    if (k <= n - k - 1) {
        cout << "YES" << endl;
        return;
    }
    if (k < n && !check(0, n - k - 1, k, n - 1))
        return;
    for (int i = max(0, n - k); i < min(n, k); i++) {
        if (a[i] != b[i]) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
