// tested on SPOJ/LPS

class manacher{
	string ac, s;
	void solve(){
		int c=0, r=0;
		for(int i=1;i<s.size();i++){
			if(r>i){
				p[i]=min(r-i,p[2*c-i]);
			}
			while((i+1+p[i]<s.size())&&
					(i-1-p[i]>=0)&&
					s[i+1+p[i]]==s[i-1-p[i]]){
				p[i]++;
			}
			if(i+p[i]>r){
				c=i;
				r=i+p[i];
			}
		}
	}
public:
	vector <int> p;
	manacher(string ac):ac(ac){
		for(int i=0;i<ac.size();i++){
			s+='$';
			s+=ac[i];
		}
		s+='$';
		p.assign(s.size(),0);
		solve();
	}
	int maxpalin(){
		int ans=1;
		for(int i=0;i<s.size();i++){
			ans=max(ans,p[i]);
		}
		return ans;
	}
	int operator[](int ind){
		return p[ind];
	}
};
