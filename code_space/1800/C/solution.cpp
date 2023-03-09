#include <iostream>
#include <queue>
using namespace std;
void solve() {
    int n, _;
    cin >> n;
    priority_queue<int> q;
    long long ans = 0;
    while (n--) {
        cin >> _;
        if (_ == 0 && q.size() > 0) {
            ans += q.top();
            q.pop();
        }
        if (_ > 0)
            q.push(_);
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
