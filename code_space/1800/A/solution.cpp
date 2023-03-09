#include <iostream>
using namespace std;
int l;
string a;
void solve() {
    cin >> l >> a;
    int cnt[4] = {0, 0, 0, 0};
    int index  = 0;
    for (int i = 0; i < l; i++) {
        if ('A' <= a[i] && a[i] <= 'Z')
            a[i] = a[i] - 'A' + 'a';
        if (a[i] == 'm' && index == 0)
            cnt[index]++;
        if (a[i] == 'e' && (index == 0 || index == 1)) {
            index = 1;
            cnt[index]++;
        }
        if (a[i] == 'o' && (index == 1 || index == 2)) {
            index = 2;
            cnt[index]++;
        }
        if (a[i] == 'w' && (index == 2 || index == 3)) {
            index = 3;
            cnt[index]++;
        }
    }
    cout << (cnt[0] + cnt[1] + cnt[2] + cnt[3] == l && cnt[0] > 0 && cnt[1] > 0 && cnt[2] > 0 && cnt[3] > 0 ? "YES" : "NO") << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}