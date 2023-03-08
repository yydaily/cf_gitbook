#include<iostream>
using namespace std;
void solve() {
	int last = -1;
	int n, now;
	cin>>n;
	while(n--) {
		cin>>now;
		while(now == 1 || (last!=-1 && now%last == 0)) now++;
		cout<<now<<' ';
		last = now;
	}
	cout<<endl;
}
int main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
