// finds z such that (a^z =(is congruent to) b (mod p)) if p is prime and a,b are known. in O(sqrt(p)) 

namespace BSGS{
	LL qpow(LL a, LL b, LL p){
		LL ans = 1, base = a;
		while (b){
			if (b & 1){
				(ans *= base) %= p;
			}
			(base *= base) %= p;
			b >>= 1;
		}
		return ans;
	}
	
	LL inv(LL x, LL p){
		return qpow(x, p - 2, p);
	}
	
	map<LL, LL> tab;
	LL bsgs(LL a, LL b, LL p){
		LL u = (LL) sqrt(p) + 1;
		LL now = 1, step;
		for (LL i = 0; i < u; i++){
			LL tmp = b * inv(now, p) % p;
			if (!tab.count(tmp)){
				tab[tmp] = i;
			}
			(now *= a) %= p;
		}
		step = now;
		now = 1;
		for (LL i = 0; i < p; i += u){
			if (tab.count(now)){
				return i + tab[now];
			}
			(now *= step) %= p;
		}
		throw;
		return -1;
	}
}