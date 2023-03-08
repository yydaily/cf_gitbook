## Labeling the Tree with Distances

You are given an unweighted tree of $$$n$$$ vertices numbered from $$$1$$$ to $$$n$$$ and a list of $$$n-1$$$ integers $$$a_1, a_2, \ldots, a_{n-1}$$$. A tree is a connected undirected graph without cycles. You will use each element of the list to label one vertex. No vertex should be labeled twice. You can label the only remaining unlabeled vertex with any integer. 

> 给定一个包含 $$$n$$$ 个节点的无权树，节点编号从 $$$1$$$ 到 $$$n$$$，并给定一个长度为 $$$n-1$$$ 的整数序列 $$$a_1, a_2, \ldots a_{n-1}$$$。树是指没有环的无向图。你会用上述的列表给每个点标号。每个节点只能被标号一次。你只能给剩下没有标号的点标号。

> 笔者注：这里有 $$$n$$$ 个节点，但是有 $$$n-1$$$ 个标号，按照题意，多出来一个节点是可以随意标号的。

A vertex $$$x$$$ is called *good* if it is possible to do this labeling so that for each vertex $$$i$$$, its label is the distance between $$$x$$$ and $$$i$$$. The distance between two vertices $$$s$$$ and $$$t$$$ on a tree is the minimum number of edges on a path that starts at vertex $$$s$$$ and ends at vertex $$$t$$$. 

> 一个节点 $$$x$$$ 被认为是 *好的* 当且仅当存在一种标号方式，使得对于所有的节点 $$$i$$$ 来说，$$$i$$$ 的标号刚好等于 $$$i$$$ 到 $$$x$$$ 的距离。两个节点 $$$s$$$ 和 $$$t$$$ 在树上的距离定义为从 $$$s$$$ 出发到达 $$$t$$$ 经过的最少路径长度。

Find all good vertices.

> 找到所有的好节点。

### Input

The first line contains one integer $$$n$$$ ($$$2\le n\le 2\cdot 10^5$$$) — the number of vertices in the tree.

> 第一行包含一个整数 $$$n$$$ ($$$2\le n\le 2\cdot 10^5$$$) —— 表示树上的节点数

The second line contains $$$n - 1$$$ integers $$$a_1,a_2,\ldots,a_{n-1}$$$ ($$$0\le a_i &lt; n$$$) — the given list.

> 第二行包含 $$$n-1$$$ 个整数 $$$a_1,a_2,\ldots,a_{n-1}$$$ ($$$0\le a_i &lt; n$$$) —— 表示上述的列表

Then, $$$n−1$$$ lines follow. Each of them contains two integers $$$u$$$ and $$$v$$$ ($$$1\le u,v\le n$$$) denoting an edge between vertices $$$u$$$ and $$$v$$$. It is guaranteed that the edges form a tree.

> 然后，有 $$$n-1$$$ 行。每一行包含两个整数 $$$u$$$ 和 $$$v$$$ ($$$1\le u,v\le n$$$) 表示在节点 $$$u$$$ 和 节点 $$$v$$$ 之间有一条边。保证这些边能头程一棵树

### Output

In the first line print the number of good vertices.

> 第一行输出好节点的数量

In the second line, print the indices of all good vertices **in ascending order**

> 第二行，**按照升序**输出所有好节点的下标

### 题解

由于我当时没想出来，后续是看题解才有的想法，所以强烈建议先看原 [题解](https://codeforces.com/blog/entry/113500)，如果还是不明白，可以再看下面的分析。

首先，我们考虑一种暴力写法，我每次都选择一个不同的节点作为根，跑一次dfs算出这个根节点的数列，然后和题目给的原数列进行比较，如果相同，那么当前节点就是好的，输出。伪代码大概如下：

```py
for node in range[1, n]:
	node_list = dfs(node)
	if input_list in node_list:
		print(node)
```

这样总复杂度是多少呢？

显然，我们枚举了每个节点，对于每个节点都需要跑一次dfs，这个复杂度是 $$$O(n^2)$$$，然后判断是否相等，也需要扫两个列表，对于图是单链的场景，每次扫的复杂度是 $$$O(n)$$$ 的，所以总复杂度是 $$$O(n^2)$$$

现在就是需要优化这个过程，其实不难发现，我们考虑这种转移——从父节点往子节点转移。

不难发现，子节点的列表，和父节点的区别是，子节点对应的子树的每个点对子节点的距离比对父节点的距离小一，而非子树的每个节点对子节点的距离比父节点距离大一。

也就是说，如果我们能维护子节点的列表，那么可以通过合并得到父节点的列表的。而不是每次都需要dfs。这样可以让第一步的复杂度优化到 $$$O(n)$$$，但是遗憾的是，每次合并的代价依然是 $$$O(n)$$$ 的，这意味着上述的第二步，复杂度仍然是 $$$O(n^2)$$$。

既然如此，我们不妨考虑第二步的合并，能否更快一点？

我们不妨将问题转换成这样，给你一个列表，让你判断多个列表是否和这个列表相同？

这个问题似乎就很显然了，一个经典做法就是判断hash值是否相同。同样的，我们可以借助这个思想，我们每次并不维护一个列表，而是维护一个hash值，只要保证这个hash是一致性hash，就能够快速的从子节点merge到父节点上。

这里详细的做法是，我们找到一个素数 $$$p$$$ ，然后每次统计hash值的时候，如果距离当前节点，距离为 $$$a$$$ 的节点有 $$$b$$$ 个，那么这部分贡献就是 $$$b \cdot p^a$$$，经过这样的设计，不难发现，每次向上或者向下转移的时候，只需要对这部分共享乘以或者除以 $$$p$$$ 就可以快速计算了。

至此，转移通过hash来解决，可以把每次转移的代价优化到 $$$O(1)$$$，也即总复杂度是 $$$O(n)$$$ 的。

但是还需要考虑一点，原题并没有给出完整的序列，而是长度为 $$$n-1$$$，这个怎么解决呢？

显然，对于多出来的任意标号，他的取值范围只能是 $$$[0, n-1]$$$，所以，不妨将初始状态的hash值，加上这些枚举构成一个序列，然后和所有节点的标号做一次取交集，交集中所有的点，都是好节点。只需要手动给所有hash值一个人为的顺序，就可以用双指针优化，将交集操作优化到 $$$O(n)$$$，但是这里由于需要排序，所以总复杂度为 $$$O(n^2)$$$

### 代码

```cpp
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
```
