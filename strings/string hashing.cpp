struct mypair{
	ll x,y;

	mypair(){x = 0; y = 0;}
	mypair(ll __x, ll __y):x(__x),y(__y){}

	mypair operator+(mypair const& obj){
		mypair res;
		res.x = x+obj.x;
		res.y = y+obj.y;
		return res;
	}

	mypair operator*(mypair const& obj){
		mypair res;
		res.x = x*obj.x;
		res.y = y*obj.y;
		return res;
	}

	mypair operator*(ll val){
		mypair res;
		res.x = x*val;
		res.y = y*val;
		return res;
	}

	mypair operator%(mypair const& obj){
		mypair res;
		res.x = x%obj.x;
		res.y = y%obj.y;
		return res;
	}

	mypair operator-(ll val){
		mypair res;
		res.x = x-val;
		res.y = y-val;
		return res;
	}

	mypair operator-(mypair const& val){
		mypair res;
		res.x = x-val.x;
		res.y = y-val.y;
		return res;
	}

	bool operator==(mypair const&val){
		return x==val.x && y == val.y;
	}
};

class Hashing
{
public:
	mypair base;
	mypair mod;
	vector<mypair> pre, inv_pow;
	mypair pow, inv;
	
	int genbase(int st, int en){
		int base = std::uniform_int_distribution<int>(st, en)(rng);
    	if(base%2 == 0){
			base--;
		}
		return base;
	}

	Hashing(vector<ll> a, int diff = 1e6+5) // number of different elements that can take in the future inputting vector
    {	
		mod = mypair((ll)1e9+123, (ll)1e9+7);
		// generate a randomized base
		base.x = genbase(diff+5, mod.x);
		base.y = genbase(diff+5, mod.y);

		pre.emplace_back(0,0);
		inv_pow.emplace_back(1, 1);

		pow = {1,1};
		inv = {powmod(base.x,mod.x-2,mod.x), powmod(base.y, mod.y-2, mod.y)};

		add(a);
    }

	Hashing (string s):Hashing(vector<ll>(s.begin(),s.end()), 350){};

	void add(vector<ll> a){
		for(auto c:a){
			pre.emplace_back((pre.back()+pow*c)%mod);
			pow = pow*base%mod;
			inv_pow.emplace_back(inv_pow.back()*inv%mod);
		}
	}

	void add(string s){
		add(vector<ll>(s.begin(),s.end()));
	}

    mypair hash(int l, int r) {
        assert(l<=r);
		assert(r < pre.size());

		mypair h = pre[r+1]-pre[l];
		if(h.x < 0){
			h.x += mod.x;
		}
		if(h.y < 0){
			h.y += mod.y;
		}

		return h*inv_pow[l]%mod;
    }

private:
    int powmod(int b, int p, int mod){
		int ans = 1;
		while(p){
			if(p&1){
				ans = 1ll*ans*b%mod;
			}

			p >>= 1;
			b = 1ll*b*b%mod;
		}
		return ans;
	}
};