#include<vector>
namespace combination {
	typedef long long ll;
	std::vector<ll> fac;
	std::vector<ll> inv;
	ll mod;
	inline ll qpow(ll a, ll b, const ll & _mod) {
		ll ret = 1;
		while(b) {
			if(b&1) ret = ret*a%_mod;
			a = a*a%_mod;
			b>>=1;
		}
		return ret;
	}
	void init(int upper, ll _mod) {
		assert(upper<=1e7);
		assert(_mod <= 1e9);
		mod = _mod;
		fac = std::vector<ll>(upper+1);
		inv = std::vector<ll>(upper+1);
		fac[0] = 1;
		for(int i = 1;i<=upper;i++) fac[i] = fac[i-1] * i % mod;
		inv[upper] = qpow(fac[upper], mod-2, mod);
		for(int i = upper-1;i>=0;i--) inv[i] = inv[i+1] * (i+1) % mod;
	}
	ll C(ll a, ll b) {
		if(a<=b) return 1;
		return fac[a] * inv[b] % mod * inv[a-b] % mod;
	}
}
