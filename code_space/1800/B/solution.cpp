#include <cstring>
#include <iostream>
using namespace std;
int n, k;
string a;
int num[26];
void solve() {
    cin >> n >> k >> a;
    memset(num, 0, sizeof(num));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if ('a' <= a[i] && a[i] <= 'z') {
            num[a[i] - 'a']++;
            if (num[a[i] - 'a'] <= 0)
                ans++;
        } else {
            num[a[i] - 'A']--;
            if (num[a[i] - 'A'] >= 0)
                ans++;
        }
    }
    for (int i = 0; i < 26; i++) {
        ans += min(k, abs(num[i]) / 2);
        k -= min(k, abs(num[i]) / 2);
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
