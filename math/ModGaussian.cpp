int rankmat(vector<vector<int>> &a){
	int n=a.size();
	int m=a[0].size();

	int r=0;
	for(int c=0; (c<m && r<n) ;c++){
		int j=r;
		for(int i=r+1;i<n;i++)
			if(a[i][c]>a[j][c]) j=i;

		if(a[j][c]==0) continue;

		swap(a[j],a[r]);

		int s=powmod(a[r][c],mod-2);
		for(int j=0;j<m;j++) a[r][j]=(1ll*a[r][j]*s)%mod;

		for(int i=0;i<n;i++){
			if(i!=r){
				int t=a[i][c];
				for(int j=0;j<m;j++){
					a[i][j]=((a[i][j]-1ll*t*a[r][j])%mod+mod)%mod;
				}
			}
		}
		r++;
	}

	return r;
}
// each first rank rows contain a single 1, to determine the coefficient value immediately
