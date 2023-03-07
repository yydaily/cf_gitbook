#include <vector>
#include <assert.h>
namespace prime {
	std::vector<int> Primes;
	std::vector<bool> sieve;
	void init(long long upper) {
		sieve = std::vector<bool>(upper+1, true);
		sieve[0] = sieve[1] = false;
		for(int i = 2;i<=upper;i++) {
			if(sieve[i]) Primes.push_back(i); // i is prime
			for(int j : Primes) {
				if(i*j > upper) break;
				sieve[i*j] = false;
				if(i%j==0) break;
			}
		}
	}
	bool is_prime(int a) {
		return sieve[a];
	}
}
