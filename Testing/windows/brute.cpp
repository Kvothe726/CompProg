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

void test_case(){
    int t; cin >> t;

    for(int tt=1;tt<=t;tt++){
        ll n,e; cin >> n >> e;
        vector<pair<pair<int,int>,int>> a(n);
        for(int i=0;i<n;i++){
            cin >> a[i].first.first >> a[i].first.second >> a[i].second;
        }

        sort(a.begin(),a.end());
        
        ll ans = 0;
        do{
            ll curx = 0, cury = LLONG_MAX;
            int dir = 1;

            ll val = 0;
            for(int i=0;i<n;i++){
                if(a[i].first.second > cury){
                    continue;
                }
                if(a[i].first.first > curx){
                    if(dir){
                        val += a[i].second;
                    }
                    else{
                        val += a[i].second-e;
                        dir ^= 1;
                    }
                }
                else if(a[i].first.first < curx){
                    if(!dir){
                        val += a[i].second;
                    }
                    else{
                        val += a[i].second-e;
                        dir ^= 1;
                    }
                }
                else{
                    val += a[i].second;
                }

                curx = a[i].first.first;
                cury = a[i].first.second;
            }

            ans = max(ans, val);
        }
        while(next_permutation(a.begin(),a.end()));

        cout << "Case #" << tt << ": " << ans << endl;
    }

    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    //cin >> t;
    while(t--){
        test_case();
    }
    return 0;
}