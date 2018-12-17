
int root(int i)
{
	while (par[i] != i)
	{
		par[i] = par[par[i]];
		i = par[i];
	}
	return i;
}

void wunion(int A, int B)
{
	int root_A = root(A);
	int root_B = root(B);
	if (Size[root_A] < Size[root_B])
	{
		par[root_A] = par[root_B];
		Size[root_B] += Size[root_A];
	}
	else
	{
		par[root_B] = par[root_A];
		Size[root_A] += Size[root_B];
	}

}

bool Find(int A, int B)
{
	if (root(A) == root(B))       //if A and B have same root,means they are connected.
		return true;
	else
		return false;
}
