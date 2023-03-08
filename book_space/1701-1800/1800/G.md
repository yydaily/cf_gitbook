## G. Symmetree

Kid was gifted a tree of $$$n$$$ vertices with the root in the vertex $$$1$$$. Since he really like *symmetrical* objects, Kid wants to find out if this tree is *symmetrica*.

> Kid获得了根节点编号为 $$$1$$$ ，总共有 $$$n$$$ 个节点的树作为礼物。由于他喜欢堆成结构，他想知道这颗树是否是对称的。

![](https://espresso.codeforces.com/8b2c94254f484755f4b58c83063231999ed42798.png)

For example, the trees in the picture above are *symmetrical*.

> 例如，上图中的树都是对称的。

![](https://espresso.codeforces.com/f73c79c68584d8484ef0eafd5d9f761a81429b2f.png)

And the trees in this picture are not *symmetrical*.

> 然而上图中的树都是不对称的。

Formally, a tree is *symmetrical* if there exists an order of children such that:

> 幸运的是，一棵树是对称的当且仅当存在一种排列子节点的方式，使得：

- The subtree of the leftmost child of the root is a mirror image of the subtree of the rightmost child; 
- the subtree of the second-left child of the root is a mirror image of the subtree of the second-right child of the root; 
- ... 
- if the number of children of the root is odd, then the subtree of the middle child should be *symmetrical*. 

> 1. 根节点最左边的子树和最右边的子树是对称的。
> 2. 根节点次左边的子树和次右边的子树是对称的。
> ...
> n. 如果根的子树数量是奇数，那么中间的子树需要是对称的。

### Input

The first line of input data contains single integer $$$t$$$ ($$$1 \le t \le 10^4$$$) — the number of test cases in the test.

> 第一行输入一个整数$$$t$$$ ($$$1 \le t \le 10^4$$$) —— 表示测试用例的数量。

The first line of each case contains an integer $$$n$$$ ($$$1 \le n \le 2 \cdot 10^5$$$) — the number of vertices in the tree.

> 每个测试用例的第一行包含一个整数$$$n$$$ ($$$1 \le n \le 2 \cdot 10^5$$$) —— 表示这棵树的节点数

The following $$$n-1$$$ lines contain two integers each $$$u$$$ and $$$v$$$ ($$$1 \le u, v \le n$$$, $$$u \neq v$$$) — indices of vertices connected by an edge.

> 接下来 $$$n-1$$$ 行，每行两个整数 $$$u$$$ 和 $$$v$$$ ($$$1 \le u, v \le n$$$, $$$u \neq v$$$) —— 白哦是一条边对应的两个端点。

It is guaranteed that the sum of $$$n$$$ over all cases does not exceed $$$2 \cdot 10^5$$$.

> 保证所有用例的 $$$n$$$ 求和不超过 $$$2 \cdot 10^5$$$。

### Output

Output $$$t$$$ strings, each of which is the answer to the corresponding test case. As an answer, output "YES" if this tree is *symmetrical*, and "NO" otherwise.

> 输出 $$$$t$$$ 个字符串，每个字符串表示测试用例的结果。输出 "YES" 表示树是对称的，反之输出 "NO"。

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

> 输出大小写字母都是可以的（例如，"yEs", "yes", "Yes", "YES" 都表示树是对称的）。

### 题解

问题的难点其实就在于如何判断两个子树是相同的，也即如何找到一个优雅的hash算法，能保证两个相同的子树hash值相同，但是又能优雅的避免冲突。

codeforces有一篇博客很好的解决了这个问题，可见 [这篇博客](https://codeforces.com/blog/entry/113465)

为了避免博客被删除，我这里额外说明一下。如果这是简单的通过到根节点的枚举次数做hash，其实是不够的，举例来说明：

```cpp
4
1 2
1 3
1 4
5
1 2
1 3
3 4
3 5
```

这两棵树的计算结果将会是一样的，计算公式都是 $$$ h(T1) = b + b*p + b*p^2 = b + p*(b + b*p) = h(T2)$$$

这个例子说明了简单hash是不可行的，原博客给出了一个更优雅的hash算法。

$$$ h(v) = 42 + \sum_{u \in sorted_by_hash(child(v))} h(u)^2 + h(u) * p^i $$$

然后对大素数取模即可。甚至不需要双模hash，单模hash也可过这个题。

### 代码

```cpp
#include<iostream>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
const long long base = 998244353;
const long long mod1 = 1e9+7;
const long long mod2 = 1e9+9;
const int _ = 2e5+10;
int n;
vector<int> edge[_];
struct poi {
    long long val1, val2;
    poi(int _v1 = 0, int _v2 = 0){
        val1 = _v1;
        val2 = _v2;
    }
    bool operator<(const poi & a) const {
        if(val1 != a.val1) return val1 < a.val1;
        return val2 < a.val2;
    }
    bool operator!=(const poi & a) const {
        return val1 != a.val1 || val2 != a.val2;
    }
    bool operator==(const poi & a) const {
        return val1 == a.val1 && val2 == a.val2;
    }
} val[_];
bool mirror[_];

void dfs(int now, int pre) {
    vector<poi> son_values;
    map<poi, int> cnt;
    val[now].val1 = val[now].val2 = 1;
    for(auto i : edge[now]) {
        if(i==pre) continue;
        dfs(i, now);
        son_values.push_back(val[i]);
        cnt[val[i]]++;
    }

    mirror[now] = true;
    auto value = poi(0, 0);
    for(auto i : cnt) {
        if(i.second % 2 == 0) continue;
        value = value != poi(0, 0)?poi(-1, -1):i.first;
    }
    if(value == poi(-1, -1)) {
        mirror[now] = false;
    } else if(value != poi(0, 0)) {
        for(auto i : edge[now]) {
            if(i==pre || val[i] != value) continue;
            mirror[now] = mirror[i];
        }
    }

    sort(son_values.begin(), son_values.end());
    val[now] = poi(41, 41);
    for(long long i = 0;i<son_values.size();i++) {
        val[now].val1 = (val[now].val1 + son_values[i].val1 * son_values[i].val1 + son_values[i].val1 * base) % mod1;
        val[now].val2 = (val[now].val2 + son_values[i].val2 * son_values[i].val2 + son_values[i].val2 * base) % mod2;
    }

}
void solve() {
    cin>>n;
    for(int i = 1, a, b;i<n;i++) {
        cin>>a>>b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }

    dfs(1, 0);

    cout<<(mirror[1]?"YES":"NO")<<endl;

    // recover
    for(int i = 1;i<=n;i++) {
        edge[i].clear();
        val[i] = 0;
        mirror[i] = false;
    }
}
int main() {
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
```
