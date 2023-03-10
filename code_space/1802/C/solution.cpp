#include <iostream>
using namespace std;
void solve() {
    int n, m;
    cin >> n >> m;
    int base = 1;
    while (base <= m)
        base *= 2;
    cout << n * m << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << i * base + j << ' ';
        }
        cout << endl;
    }
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}

