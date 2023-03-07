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