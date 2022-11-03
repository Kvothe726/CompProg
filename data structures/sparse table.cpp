#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int k = 25, maxn = 200005;

int st[k+1][maxn];
int lg[maxn+1];

// this gives a constant time query.
int prod(int l, int r){
    int i = lg[r - l + 1];
    return __gcd(st[i][l], st[i][r - (1 << i) + 1]); // call any idempotent functions here.
}

void test_case(){
    int n; cin >> n;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
    }

    copy(a.begin(), a.end(), st[0]);
    for(int i=1;i<=k;i++){
        for(int j=0; j+(1<<i) <= n; j++){
            st[i][j] = __gcd(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
    
    // query here
    prod(2,3);
    return;
}

int main(){
    lg[1] = 0;
    for (int i = 2; i <= maxn; i++)
        lg[i] = lg[i/2] + 1;
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    while(t--){
        test_case();
    }
    return 0;
}