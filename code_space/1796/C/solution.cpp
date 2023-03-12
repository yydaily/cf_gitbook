#include<iostream>
#include<map>
#include<queue>
using namespace std;
int l, r;
int cal(long long now, long long b) {
	int ans = 1;
	while(now*b <= r) {
		ans++;
		now*=b;
	}
	return ans;
}
void solve() {
	cin>>l>>r;
	int max_len = cal(l, 2)-1;

	int base1 = 1<<max_len;
	long long ans = max(0, r/base1 - l + 1);

	int base2 = base1/2*3;
	ans += max(0, r/base2 - l + 1) * max_len;

	cout<<max_len+1<<' '<<ans<<endl;
}
int main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
