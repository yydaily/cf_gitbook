#include<iostream>
using namespace std;
string ans = "FBFFBFFBFBFFBFFBFBFFBFFB", x;
void solve() {
	int _;
	cin>>_>>x;
	if(ans.find(x) != -1) {
		cout<<"YES"<<endl;
	}
	else cout<<"NO"<<endl;
}
int main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
