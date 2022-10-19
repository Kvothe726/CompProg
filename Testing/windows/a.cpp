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
        map<ll, vector<pair<ll,ll>>> mp;
        for(int i=0;i<n;i++){
            ll x,y,c; cin >> x >> y >> c;
            mp[y].emplace_back(x,c);
        }
        mp[1000000005].emplace_back(0,0);

        // compress y's
        vector<vector<ll>> c,x;
        for(auto &pr:mp){
            sort(pr.second.begin(), pr.second.end());
            if(pr.second[0].first != 0){
                pr.second.insert(pr.second.begin(),make_pair(0ll,0ll));
            }
            pr.second.emplace_back(1000000,0);

            c.emplace_back();
            x.emplace_back();
            for(auto p:pr.second){
                c.back().emplace_back(p.second);
                x.back().emplace_back(p.first);
            }
        }

        int m = c.size();
        vector<vector<ll>> pre(m),suf(m);
        for(int i=0;i<m;i++){
            pre[i].resize(c[i].size());
            for(int j=0;j<c[i].size();j++){
                pre[i][j] = c[i][j];
                if(j){
                    pre[i][j] += pre[i][j-1];
                }
            }
        }

        for(int i=0;i<m;i++){
            suf[i].resize(c[i].size());
            for(int j=c[i].size()-1;j>=0;j--){
                suf[i][j] = c[i][j];
                if(j+1<c[i].size()){
                    suf[i][j] += suf[i][j+1];
                }
            }
        }

        vector<vector<pair<ll,ll>>> dp(m), zdp(m), mxdp(m);
        for(int i=0;i<m;i++){
            int sz = c[i].size();
            dp[i].resize(sz);
            zdp[i].resize(sz);

            // solve for zdp first in the left direction
            for(int j=0;j<sz;j++){
                zdp[i][j].first = c[i][j];
                if(j){
                    zdp[i][j].first += zdp[i][j-1].first;
                }

                // or simply go down
                if(i){
                    ll cur = c[i][j];
                    auto it = upper_bound(x[i-1].begin(), x[i-1].end(), x[i][j])-x[i-1].begin();
                    zdp[i][j].first = max(zdp[i][j].first, cur+dp[i-1][it-1].first);
                }
            }

            // solve for zdp first in the right direction
            for(int j=sz-1;j>=0;j--){
                zdp[i][j].second = c[i][j];
                if(j+1 < sz){
                    zdp[i][j].second += zdp[i][j+1].second;
                }

                // or simply go down
                if(i){
                    ll cur = c[i][j];
                    auto it = lower_bound(x[i-1].begin(), x[i-1].end(), x[i][j])-x[i-1].begin();
                    zdp[i][j].second = max(zdp[i][j].second, cur+dp[i-1][it].second);
                }
            }


            // now solve for dp in the left direction
            for(int j=0;j<sz;j++){
                // use zero turns
                dp[i][j].first = zdp[i][j].first;

                // use 1 turn
                // go down at the left of this point
                ll cur = pre[i][j];
                if(i){
                    auto it = upper_bound(x[i-1].begin(),x[i-1].end(), x[i][j])-x[i-1].begin();
                    cur += mxdp[i-1][it-1].second;
                }
                dp[i][j].first = max(dp[i][j].first, cur-e);
                // go down at right of this point
                dp[i][j].first = max(dp[i][j].first, pre[i][j]-c[i][j]+zdp[i][j].second-e);

                // use two turns
                dp[i][j].first = max(dp[i][j].first, pre[i][sz-1]+(i?mxdp[i-1][0].first:0)-2*e);
            }

            for(int j=sz-1;j>=0;j--){
                // use zero turns
                dp[i][j].second = zdp[i][j].second;

                // use 1 turn
                // go down to the right of this point
                ll cur = suf[i][j];
                if(i){
                    auto it = lower_bound(x[i-1].begin(), x[i-1].end(), x[i][j])-x[i-1].begin();
                    cur += mxdp[i-1][it].first;                    
                }
                dp[i][j].second = max(dp[i][j].second, cur-e);
                // go down to the left of this point
                dp[i][j].second = max(dp[i][j].second, suf[i][j]-c[i][j]+zdp[i][j].first-e);

                // use two turns
                dp[i][j].second = max(dp[i][j].second, pre[i][sz-1]+(i?mxdp[i-1][c[i-1].size()-1].second:0)-2*e);
            }

            // compute mxdps
            mxdp[i].resize(sz);
            for(int j=0;j<sz;j++){
                mxdp[i][j].second = dp[i][j].second;
                if(j){
                    mxdp[i][j].second = max(mxdp[i][j].second, mxdp[i][j-1].second);
                }
            }

            for(int j=sz-1;j>=0;j--){
                mxdp[i][j].first = dp[i][j].first;
                if(j+1<sz){
                    mxdp[i][j].first = max(mxdp[i][j].first, mxdp[i][j+1].first);
                }
            }
        }

        cout << "Case #" << tt << ": " << dp[m-1][0].second << endl;
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