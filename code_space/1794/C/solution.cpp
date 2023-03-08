#include<iostream>
#include<vector>
using namespace std;

int len;
void solve() {
	cin>>len;
	vector<int> num(len);
	int index = 0;
	for(int i = 0;i<len;i++) {
		cin>>num[i];
		while(index<=i && num[index] < i+1-index) index++;
		cout<<i-index+1<<' ';
	}
	cout<<endl;
}
int main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
