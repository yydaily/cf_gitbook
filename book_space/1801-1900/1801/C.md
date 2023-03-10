## E. Music Festival

The boy Vitya loves to listen to music very much. He knows that $$$n$$$ albums are due to be released this Friday, $$$i$$$-th of which contains $$$k_i$$$ tracks. Of course, Vitya has already listened to all the tracks, and knows that in the $$$i$$$-th album, the coolness of the $$$j$$$-th track is equal to $$$a_{i,j}$$$.

> 张三非常喜欢听音乐，他知道在这周五将会有 $$$n$$$ 张唱片会发布，其中第 $$$i$$$ 张唱片包含 $$$k_i$$$ 首歌。显然，张三已经听过所有的歌，并且知道在第 $$$i$$$ 张唱片里面第 $$$j$$$ 首歌的好听程度为 $$$a_{i, j}$$$。

Vitya has a friend Masha, whom he really wants to invite to the festival, where his favorite bands perform. However, in order for a friend to agree, she must first evaluate the released novelties. Vitya knows that if Masha listens to a track that was cooler than all the previous ones, she will get 1 unit of impression. Unfortunately, albums can only be listened to in their entirety, without changing the songs in them in places.

> 张三有个朋友王麻子，并且想邀请他去音乐节。然而，为了说服朋友去，他必须评估这场音乐节。张三知道，如果王麻子听到某首歌的好听程度超过之前所有听过的歌，他会获得 $$$1$$$ 点印象。不幸的是，唱片必须完整的听完，不能跳着听不同的唱片。

Help Vitya find such an order of albums so that Masha's impression turns out to be as much as possible, and she definitely went to the festival with him. 

> 帮助张三找到听唱片的顺序，使得王麻子的印象尽可能多，这样他才愿意和张三一起去音乐节。

### Input

Each test consists of multiple test cases. The first line contains a single integer t ($$$1 \le t \le 200\,000$$$) — the number of test cases. The description of test cases follows.

> 输入包含多组样例，第一行包含一个整数t ($$$1 \le t \le 200\,000$$$) —— 表示测试用例的数量，然后是每组测试用例的描述。

The first line of each test case contains a single integer $$$n$$$ ($$$1 \le n \le 200\,000$$$) — number of albums.

> 第一行包含一个整数$$$n$$$ ($$$1 \le n \le 200\,000$$$) —— 表示唱片的数量。

The album descriptions follow. Each album description consists of two lines:

> 接下来是唱片的描述，每个唱片包含两行输入：

The first line contains a single integer $$$k_i$$$ ($$$1 \le k_i \le 200\,000$$$) — the number of tracks in the $$$i$$$th album.

> 第一行包含一个整数$$$k_i$$$ ($$$1 \le k_i \le 200\,000$$$) —— 表示唱片包含的歌曲数。

The following line contains $$$k_i$$$ integers $$$a_{i, 1},\ a_{i, 2},\ a_{i, 3},\ \ldots,\ a_{i, k_i}$$$ ($$$1 \le a_{i,j} \le 200\,000$$$) — the coolness of the tracks in the $$$i$$$ album. 

> 接下来一行包含 $$$k_i$$$ 个整数$$$a_{i, 1},\ a_{i, 2},\ a_{i, 3},\ \ldots,\ a_{i, k_i}$$$ ($$$1 \le a_{i,j} \le 200\,000$$$) —— 表示第 $$$i$$$ 张唱片每首歌的好听程度。

Denote for $$$\sum k_i$$$ the sum of all $$$k_i$$$. It is guaranteed that $$$\sum k_i \le 200\,000$$$. 

> 定义 $$$\sum k_i$$$ 为 $$$k_i$$$ 的和，保证 $$$\sum k_i \le 200\, 000$$$。

### Output

For each test case print the singular number  — the maximum impression that Masha can get. 

> 对于每个测试用例输出一个整数 —— 表示王麻子能获得的印象点数。

### 题解

首先，对于一张唱片来说，一定可以处理成递增的，并且不影响答案。例如，某张唱片是 $$$[1, 9, 5, 7, 8]$$$，他对答案的共享和 $$$[1, 9]$$$ 对答案的贡献一模一样。原因是，如果某个地方开始递减了，后面递减的歌曲显然不会提供贡献，不如直接去掉。

基于上面的想法，我们默认每张唱片都是一个递增序列。

现在考虑某张唱片对答案的影响，假设之前已经存在 $$$n$$$ 张唱片，当前唱片有 $$$m$$$ 首歌曲（对应的序列为 $$$[a_1, a_2, \ldots, a_m]$$$ ，看他插入对答案的影响。

如果之前某张唱片的最后一首歌的好听程度是 $$$x$$$，这张唱片接在后面，对答案的影响是什么呢？ 显然，如果 $$$x>=a_m$$$ ，那么这张唱片不会提供任何贡献，反之，如果存在 $$$a_i > x$$$，那么接下来的几首歌都会对答案产生贡献，也即 $$$a_i, \ldots, a_m$$$ 这几首歌都会增加一个印象点。

这样，我们可以快速计算，当最后一张唱片是当前唱片时，能得到的最大印象点是多少。只需要枚举每张听过的唱片，接到他们后面，得到的答案取 max 就是当前唱片作为收尾的贡献。这样只需要 for for就可以得到答案。但是这样复杂度太高了。

我们考虑优化这个过程，假设存在两张唱片的最后一首歌，分别为 $$$x, y$$$，不妨设 $$$x<y$$$，如果存在 $$$i$$$ 使得 $$$a_i < x < y < a_{i+1}$$$，实际上我们就并不需要统计 $$$x$$$ 对本唱片的贡献。因为 $$$y$$$ 唱片作为结尾的印象点一定是大于 $$$x$$$ 的（不难证明，如果 $$$x$$$ 的点数是大于等于$$$y$$$的，我只需要让 $$$y$$$ 接在 $$$x$$$ 后面，显然贡献更大）。

也就是说，对于每个 $$$a_i$$$，理论上我需要找到一个比 $$$a_i$$$ 稍小的唱片 $$$y$$$ ，那么本唱片的贡献 = $$$y$$$ 唱片的贡献 + $$$m-i+1$$$，这个数据结构可以直接用set搞定。

然后需要注意的是插入顺序。一定要让结尾小的先插入，这样可以保证统计结尾大的答案的时候不会偏小。

### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
void input(vector<int> &ret) {
    ret.clear();
    int len, buf;
    cin >> len;
    while (len--) {
        cin >> buf;
        if (ret.size() == 0 || buf > ret[ret.size() - 1])
            ret.push_back(buf);
    }
}
const int _ = 2e5 + 10;
vector<int> vs[_];
bool cmp(const vector<int> &a, const vector<int> &b) { return a[a.size() - 1] < b[b.size() - 1]; }
struct poi {
    int val;
    int len;
    poi(int _v = 0, int _l = 0) {
        val = _v;
        len = _l;
    }
    bool operator<(const poi &a) const {
        if (val != a.val)
            return val < a.val;
        return len < a.len;
    }
};
void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        input(vs[i]);
    sort(vs, vs + n, cmp);
    set<poi> s;
    s.insert(poi(0, 0));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int buf = 0;
        for (int j = 0; j < vs[i].size(); j++) {
            auto x = s.lower_bound(poi(vs[i][j], 0));
            x--;
            buf = max(buf, (*x).len + int(vs[i].size()) - j);
        }
        s.insert(poi(vs[i][vs[i].size() - 1], buf));
        ans = max(ans, buf);
    }
    cout << ans << endl;
}
int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```
