## Counting Factorizations

The prime factorization of a positive integer $$$m$$$ is the unique way to write it as $$$\displaystyle m=p_1^{e_1}\cdot p_2^{e_2}\cdot \ldots \cdot p_k^{e_k}$$$, where $$$p_1, p_2, \ldots, p_k$$$ are prime numbers, $$$p_1 < p_2 < \ldots < p_k$$$ and $$$e_1, e_2, \ldots, e_k$$$ are positive integers. 
> 一个正整数 $$$m$$$ 的素因数分解只能写成如下唯一的一种形式：$$$\displaystyle m=p_1^{e_1}\cdot p_2^{e_2}\cdot \ldots \cdot p_k^{e_k}$$$，其中 $$$p_1, p_2, \ldots, p_k$$$ 都是素数，并且 $$$p_1 < p_2 < \ldots < p_k$$$，$$$e_1, e_2, \ldots, e_k$$$ 都是正整数。

For each positive integer $$$m$$$, $$$f(m)$$$ is defined as the multiset of all numbers in its prime factorization, that is $$$f(m)=\{p_1,e_1,p_2,e_2,\ldots,p_k,e_k\}$$$. 
> 对于每个正整数 $$$m$$$，定义 $$$f(m)$$$ 是素数分解中所有数字组成的多重集，也即$$$f(m)=\{p_1,e_1,p_2,e_2,\ldots,p_k,e_k\}$$$。

For example, $$$f(24)=\{2,3,3,1\}$$$, $$$f(5)=\{1,5\}$$$ and $$$f(1)=\{\}$$$.
> 例如，$$$f(24)=\{2,3,3,1\}$$$, $$$f(5)=\{1,5\}$$$ and $$$f(1)=\{\}$$$。

You are given a list consisting of $$$2n$$$ integers $$$a_1, a_2, \ldots, a_{2n}$$$. Count how many positive integers $$$m$$$ satisfy that $$$f(m)=\{a_1, a_2, \ldots, a_{2n}\}$$$. Since this value may be large, print it modulo $$$998\,244\,353$$$.
> 给你一个长度为 $$$2n$$$ 的列表 $$$a_1, a_2, \ldots, a_{2n}$$$。问有多少个正整数 $$$m$$$ 满足 $$$f(m) = \{a_1, a_2, \ldots, a_{2n}\}$$$。由于答案可能很大，将答案对 $$$998\,244\,353$$$ 取模。

### Input

The first line contains one integer $$$n$$$ ($$$1\le n \le 2022$$$).
> 第一行输入一个整数 $$$n$$$ ($$$1\le n \le 2022$$$)

The second line contains $$$2n$$$ integers $$$a_1, a_2, \ldots, a_{2n}$$$ ($$$1\le a_i\le 10^6$$$)  — the given list.
> 第二行输入 $$$2n$$$ 个整数$$$a_1, a_2, \ldots, a_{2n}$$$ ($$$1\le a_i\le 10^6$$$) —— 也就是上文提到的列表

### Output

Print one integer, the number of positive integers $$$m$$$ satisfying $$$f(m)=\{a_1, a_2, \ldots, a_{2n}\}$$$ modulo $$$998\,244\,353$$$.
> 输出一个整数，表示有多少个 $$$m$$$ 满足 $$$f(m)=\{a_1, a_2, \ldots, a_{2n}\}$$$ modulo $$$998\,244\,353$$$

### 题解

首先，根据题意，如果存在多个 $$$a_i$$$ 都是同一个质数，例如 $$$a_2 = a_3 = 5$$$，那么必定至少有一个是指数，因为根据题目的定义，每个底数都是不相同的。

根据这个想法，我们可以人为的将列表拆成两个部分，一部分是底数，一部分是指数。但是我们并不能很快速的确定哪些是指数哪些是底数，但是根据上面的性质，我们至少能知道有些数必定是指数。

基于此，那么一个自然的想法就是我们统计每个数字出现了多少次，得到一系列数组 $$$[b_i, cnt_i]$$$ 表示 $$$b_i$$$ 这个数据出现了 $$$cnt_i$$$ 次。

那么不难想到：

1. 如果 $$$b_i$$$ 是合数，那么都只能作为指数，他们对答案的贡献就是 $$$C_n^{cnt_i}$$$ ，也就是从之前的底数里面挑 $$$cnt_i$$$ 个出来，他们的指数是 $$$b_i$$$了。
2. 如果 $$$b_i$$$ 是素数，那么就有两种可能，一种和上面的case一样，还有一种可能就是，有一个是底数，其他的是指数，对答案的贡献就是 $$$C_n^{cnt_i-1}$$$

如此，一个很自然的二维DP转移可以得到答案。

定义：$$$dp[i][j]$$$ 表示用了前 $$$i$$$ 种数字，其中有 $$$j$$$ 个数字成了指数。那么考虑转移：

1. 如果 $$$b_i$$$ 是合数，$$$dp[i][j] += dp[i-1][j-cnt_i] * C_{n-(j-cnt_i)}^{cnt_i}$$$，这里减去了之前已经选择的位置。
2. 如果 $$$b_i$$$ 是素数，还多一个转移 $$$dp[i][j] += dp[i-1][j-cnt_i+1] * C_{n-(j-cnt_i+1)}^{cnt_i-1}$$$

### 代码

```cpp
#include "../../template/combination.cpp"
#include "../../template/prime.cpp"
#include <algorithm>
#include <iostream>
#include <vector>
const int mod = 998244353;
using namespace std;
int n;
long long dp[4050][2025];
int d[4050];
void handle(int cnt, int data, int &last_index) {
    bool is_prime = prime::is_prime(data);
    for (int j = 0; j < 2025; j++) {
        if (j + cnt - 1 >= 2025)
            continue;
        if (dp[last_index][j] == 0)
            continue;
        if (is_prime)
            dp[last_index + 1][j + cnt - 1] = (dp[last_index + 1][j + cnt - 1] + (dp[last_index][j] * combination::C(n / 2 - j, cnt - 1)) % mod) % mod;
        dp[last_index + 1][j + cnt] = (dp[last_index + 1][j + cnt] + (dp[last_index][j] * combination::C(n / 2 - j, cnt)) % mod) % mod;
    }
    last_index++;
}
int main() {
    prime::init(1e6);                 // 初始化素数，用于后续做判断
    combination::init(1e6 + 10, mod); // 组合数相关的初始化
    cin >> n;
    n *= 2;
    for (int i = 0; i < n; i++)
        cin >> d[i];
    sort(d, d + n); // 排序是为了后面好统计数据

    int index = 0;
    dp[0][0]  = 1;

    int last = 0;
    int cnt  = 1;
    for (int i = 1; i < n; i++) {
        if (d[i] == d[last]) {
            cnt++;
            last = i;
            continue;
        }

        handle(cnt, d[last], index); // 数据出现了多少次，数据是什么，上一次dp的下标
        last = i;
        cnt  = 1;
    }
    handle(cnt, d[last], index); // 最后别忘了额外处理一次
    cout << dp[index][n / 2] << endl;
    return 0;
}
```
