/*If in any problem you want to use any data structure two times (ex. two seg trees in the same problem) just create a class for it and create two object instances*/

#include <iostream>
#include <climits>
#define nmax 100005
using namespace std;
int st[4*nmax],lazy[4*nmax]={0};
void buildst(int *a,int start,int end,int node){
	if(start==end)st[node]=a[start];
	else if(start<end){
		int mid=(start+end)/2,left=2*node+1,right=left+1;
		buildst(a,start,mid,left);
		buildst(a,mid+1,end,right);
		st[node]=min(st[left],st[right]);
	}
}
void update(int start,int end,int l,int r,int dif,int node){
	if(lazy[node]!=0){
		// there are pending updates
		st[node]+=lazy[node];
		if(start!=end){
			lazy[2*node+1]+=lazy[node];
			lazy[2*node+2]+=lazy[node];
		}
		lazy[node]=0;
	}
	if(start> r or end<l)return;
	else if(start>=l and end<=r){
		st[node]+=dif;	// make the update for the current range and keep them pending for the child nodes
		if(start!=end){
			lazy[2*node+1]+=dif;
			lazy[2*node+2]+=dif;
		}
		return;
	}
	int mid=(start+end)/2;
	update(start,mid,l,r,dif,2*node+1);
	update(mid+1,end,l,r,dif,2*node+2);
	st[node]=min(st[2*node+1],st[2*node+2]);
}
int queryMin(int start,int end,int l,int r,int node){
	if(lazy[node]!=0){
		// if there are updates pending, apply them before making the queries
		st[node]+=lazy[node];
		if(start!=end){
			lazy[2*node+1]+=lazy[node];
			lazy[2*node+2]+=lazy[node];
		}
		lazy[node]=0;
	}
	if(start>r or end<l)return INT_MAX-1;
	else if(start>=l and end<=r)return st[node];
	else{
		int mid=(start+end)/2,left=2*node+1,right=left+1;
		return min(queryMin(start,mid,l,r,left),queryMin(mid+1,end,l,r,right));
	}
}

int main(){

}
