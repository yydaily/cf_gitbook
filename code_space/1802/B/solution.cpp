#include <iostream>
using namespace std;
int n, a;
void solve() {
    cin >> n;
    int ans   = 0;
    int cages = 0;
    int num   = 0;
    while (n--) {
        cin >> a;
        if (a == 2) {
            if (num <= 2)
                continue;
            int cage_use = (num - 2) / 2 + num % 2;
            cages += cage_use;
            num -= cage_use * 2;
            num = max(num, 0);
        } else {
            num++;
            ans = max(ans, cages + num);
        }
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
