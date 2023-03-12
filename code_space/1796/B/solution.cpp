#include<iostream>
using namespace std;
string a,b;
void solve() {
	cin>>a>>b;
	if(a[0] == b[0]) {
		cout<<"YES"<<endl;
		cout<<a[0]<<"*"<<endl;
		return ;
	}
	if(a[a.length()-1] == b[b.length()-1]) {
		cout<<"YES"<<endl;
		cout<<"*"<<a[a.length()-1]<<endl;
		return ;
	}
	for(int i = 0;i<a.length()-1;i++) {
		for(int j = 0;j<b.length()-1;j++) {
			if(a[i] == b[j] && a[i+1] == b[j+1]) {
				cout<<"YES"<<endl;
				cout<<"*"<<a[i]<<a[i+1]<<"*"<<endl;
				return ;
			}
		}
	}
	
	cout<<"NO"<<endl;
}
int main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
