#include <iostream>
using namespace std;
int n;
string a;
void solve() {
    cin >> n >> a;
    int ans = 1;
    for (int i = 2; i < n; i++) {
        if (a[i] == a[i - 2])
            continue;
        ans++;
    }
    cout << ans << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
