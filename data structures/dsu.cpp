int root(int Arr[], int i)
{
	while (Arr[i] != i)
	{
		Arr[i] = Arr[Arr[i]];
		i = Arr[i];
	}
	return i;
}

void wunion(int Arr[], int Size[], int A, int B)
{
	int root_A = root(Arr, A);
	int root_B = root(Arr, B);
	if (Size[root_A] < Size[root_B])
	{
		Arr[root_A] = Arr[root_B];
		Size[root_B] += Size[root_A];
	}
	else
	{
		Arr[root_B] = Arr[root_A];
		Size[root_A] += Size[root_B];
	}

}

bool find(int Arr[], int A, int B)
{
	if (root(Arr, A) == root(Arr, B))       //if A and B have same root,means they are connected.
		return true;
	else
		return false;
}
