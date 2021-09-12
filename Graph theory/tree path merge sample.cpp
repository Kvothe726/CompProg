// this code is just a sample for understanding
// We maintain two data structures one is the original tree as par and
// A dsu that merges a path in the tree, and root of each component is the highest node from bottom.
// To update on a path(u,v) leaving already updated edges, let l = lca(u,v) and do paint(u,l,val,ans) and same for v
// imagine a tree path (node -> ancestor) as a path with bunch of already connected components in middle.
// imagine the paints are being performed on the original tree and "ans" will contain exactly that after each paint.

par[19][MAXN];
int pa[MAXN], ans[MAXN];
 
int paint(int s, int l, int v, int *ans){
	if(s != pa[s]) return pa[s] = paint(pa[s], l, v, ans);
	if(dep[s] <= dep[l]) return s;
	else{
		ans[s] = v;
		return pa[s] = paint(par[0][s], l, v, ans);
	}
}