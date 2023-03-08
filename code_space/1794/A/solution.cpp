#include<iostream>
using namespace std;
int n;
string a, b[2];
void solve() {
	cin>>n;
	int x = 2*n-2;
	int index = 0;
	while(x--) {
		cin>>a;
		if(a.length()== n-1) {
			b[index++] = a;
		}
	}
	if(b[0].substr(1, n-2).compare(b[1].substr(0, n-2)) == 0) {
		b[0] = b[0] + b[1].substr(n-2, 1);
	} else {
		b[0] = b[1] + b[0].substr(n-2, 1);
	}
	for(int i = 0;i<n;i++) {
		if(b[0][i] != b[0][n-i-1]) {
			cout<<"NO"<<endl;
			return;
		}
	}
	cout<<"YES"<<endl;
}
int main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
