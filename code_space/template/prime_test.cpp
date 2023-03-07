#include "./prime.cpp"
#include <iostream>
using namespace prime;
int main() {
	init(100);
	for(auto i : Primes) {
		std::cout<<i<<std::endl;
	}
	return 0;
}
