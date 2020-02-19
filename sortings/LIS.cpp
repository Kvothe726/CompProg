//multiple equal elements are allowed.

void LIS(vector<int> a, vector<int>& dp){ //dp[i] max non dec subsequence ending at i.
	int n=a.size();
	vector<int> d(n+1,1e9);
	d[0]=-1e9;

	for(int i=0;i<n;i++){
		auto it=upper_bound(d.begin(),d.end(),a[i]); // for strictly increasing change it to lower_bound
		*it=a[i];
		dp[i]=it-d.begin();
	}
}

/*for decreasing subsequence, or max len subsequence starting from index
you can reverse the original array, negate it or both.
*/
