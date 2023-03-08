#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
const int _          = 2e5 + 10;
const long long base = 998244353;
const long long mod1 = 1e9 + 7;
const long long mod2 = 1e9 + 9;
long long base1[_], base2[_];
void init() {
    base1[0] = base2[0] = 1;
    for (int i = 1; i < _; i++) {
        base1[i] = (base1[i - 1] * base) % mod1;
        base2[i] = (base2[i - 1] * base) % mod2;
    }
}
int n;
struct poi {
    int index;
    long long val1, val2;
    poi(long long _v1 = 0, long long _v2 = 0) {
        val1 = _v1;
        val2 = _v2;
    }
    void add(long long cnt, int index) {
        val1 = (val1 + cnt * base1[index]) % mod1;
        val2 = (val2 + cnt * base2[index]) % mod2;
    }
    void add(const poi &a) {
        val1 = (val1 + a.val1 * base) % mod1;
        val2 = (val2 + a.val2 * base) % mod2;
    }
    poi operator-(const poi &a) const { return poi(((val1 - a.val1 * base) % mod1 + mod1) % mod1, ((val2 - a.val2 * base) % mod2 + mod2) % mod2); }
    bool operator==(const poi &a) const { return a.val1 == val1 && a.val2 == val2; }
    bool operator<(const poi &a) const {
        if (val1 != a.val1)
            return val1 < a.val1;
        return val2 < a.val2;
    }
} start[_], point[_];
vector<int> sons[_];
void input() {
    cin >> n;
    map<int, int> m;
    for (int i = 1, a; i < n; i++) {
        cin >> a;
        m[a]++;
    }
    for (auto i : m)
        start[0].add(i.second, i.first);
    for (int i = n - 1; i >= 0; i--) {
        start[i] = start[0];
        start[i].add(1, i);
    }
    sort(start, start + n);
    for (int i = 1, a, b; i < n; i++) {
        cin >> a >> b;
        sons[a].push_back(b);
        sons[b].push_back(a);
    }
}
void dfs1(int now = 1, int pre = 0) {
    point[now].val1 = point[now].val2 = 1;
    for (auto i : sons[now]) {
        if (i == pre)
            continue;
        dfs1(i, now);
        point[now].add(point[i]);
    }
}
void dfs2(int now = 1, int pre = 0) {
    if (now != 1)
        point[now].add(point[pre] - point[now]);
    for (auto i : sons[now]) {
        if (i == pre)
            continue;
        dfs2(i, now);
    }
}
void merge() {
    for (int i = 1; i <= n; i++)
        point[i].index = i;
    sort(point + 1, point + n + 1);
    int index = 0;
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        while (index < n && start[index] < point[i])
            index++;
        if (start[index] == point[i])
            ans.push_back(point[i].index);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto i : ans)
        cout << i << ' ';
    cout << endl;
}
int main() {
    init();  // 初始化底数
    input(); // 处理输入并预处理原本的hash值
    dfs1();  // 第一次dfs统计出所有子树的hash值
    dfs2();  // 第二次dfs统计每个节点的真实hash值
    merge(); // 合并统计结果
    return 0;
}