#include <iostream>
#include <map>
using namespace std;
const int __ = 2e5 + 10;
int n;
struct poi {
    int a, b;
    string _;
    void input() {
        cin >> _;
        for (auto i : _) {
            a |= (1 << (i - 'a'));
            b ^= (1 << (i - 'a'));
        }
    }
} d[__];
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        d[i].input();
    }
    long long ans = 0;
    for (int i = 0; i <= 25; i++) {
        map<int, int> m;
        for (int j = 0; j < n; j++) {
            if (d[j].a & (1 << i))
                continue;
            m[d[j].b]++;
        }
        int now = (1 << 26) - 1 - (1 << i);
        for (auto j : m) {
            if (j.first < now - j.first)
                ans += 1LL * j.second * m[now - j.first];
            else if (j.first == now - j.first)
                ans += 1LL * j.second * (j.second - 1) / 2;
        }
    }
    cout << ans << endl;
    return 0;
}
