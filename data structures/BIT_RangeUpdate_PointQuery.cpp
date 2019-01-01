#define LSOne(S) (S & (-S))
ll ft[500005]={};

// Point query: Returns the value at position b in the array
ll query(int b)	{
    b++;
	ll sum = 0;
	for (; b; b -= LSOne(b)) sum += ft[b];
	return sum;
}

// Point update: Adds v to the value at position k in the array
void update(int kx, ll v) {
	for (; kx <= n; kx += LSOne(kx)) ft[kx] += v;
}

// Range update: Adds v to each element in [i...j] in the array
void range_update(int i, int j, ll v)	{
    i++,j++;  // the indexes i,j given from caller function are 0indexed.
	update(i, v);
	update(j + 1, -v);
}
