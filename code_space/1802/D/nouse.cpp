#include<iostream>
#include<set>
using namespace std;
int main() {
	multiset<int> s;
	for(int i = 1;i<10;i++) s.insert(i);
	auto y = s.begin();
	auto x = y;
	x++;
	cout<<(*x)<<endl;
	cout<<(*y)<<endl;
	return 0;
}
