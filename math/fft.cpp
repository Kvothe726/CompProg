#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template<typename T> struct cp {
	T x, y;
	cp<T> operator+(const cp &o) const {
		return {x+o.x, y+o.y};
	}
	cp<T> operator*(const cp &o) const {
		return {x*o.x-y*o.y, x*o.y+y*o.x};
	}
};

template<typename T> void fft(vector<cp<T>> &a, bool iv) {
	int n=a.size();
	for(int i=0, j=0; i<n; ++i) {
		if(i>j)
			swap(a[i], a[j]);
		for(int k=n/2; (j^=k)<k; k/=2);
	}
	for(int st=1; 2*st<=n; st*=2) {
		T an=acos((T)-1)/st*(iv?-1:1);
		cp<T> wn={cos(an), sin(an)}, wi={1, 0};
		for(int i=0; i<n; i+=2*st) {
			cp<T> wi={1, 0};
			for(int j=i; j<i+st; ++j, wi=wi*wn) {
				cp<T> u=a[j], v=wi*a[j+st];
				a[j]=u+v;
				a[j+st]=u+v*cp<T>{-1, 0};
			}
		}
	}
	if(iv)
		for(int i=0; i<n; ++i)
			a[i].x/=n;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	vector<cp<double>> a(1<<4),b(1<<4); //initialize for final array size in pows of 2
	for(int i=0;i<(1<<2);i++){
		a[i].x=1;
	}
	for(int i=0;i<(1<<3);i++){
		b[i].x=1;
	}

	fft(a,0);
	fft(b,0);

	for(int i=0;i<(1<<4);i++){
		a[i]=a[i]*b[i];
	}

	fft(a,1);

	for(int i=0;i<(1<<4);i++){
		cout << ll(round(a[i].x)) << " ";
	}
	cout << endl;
	return 0;
}
