#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

typedef long long ll;

void test_case(){
    string s; cin >> s;
    int n = s.size();

    map<char, int> mp;
    for(auto c:s){
        mp[c]++;
    }

    if(mp.size() == 1){
        cout << s << endl;
        return;
    }

    bool is = 0;
    char c;
    for(auto p:mp){
        if(p.second == 1){
            c = p.first;
            is = 1;
            break;
        }
    }

    if(is){
        string t;
        t+=c;
        sort(s.begin(),s.end());
        for(auto ch:s){
            if(ch!=c){
                t+=ch;
            }
        }
        cout << t << endl;
        return;
    }

    int fsz = mp.begin()->second;
    if(fsz <= n-fsz+2){
        char fc = mp.begin()->first;
        string t;
        t+=fc;
        t+=fc;
        mp[fc]-=2;

        string rem;
        for(auto ch:s){
            if(ch!=fc){
                rem+=ch;
            }
        }
        sort(rem.begin(),rem.end());
        reverse(rem.begin(),rem.end());

        for(int i=0;i<n-2;i++){
            if(i&1){
                if(mp[fc]>0){
                    mp[fc]--;
                    t+=fc;
                }
                else{
                    t+=rem.back();
                    rem.pop_back();
                }
            }
            else{
                t+=rem.back();
                rem.pop_back();
            }
        }
        cout << t << endl;
    }
    else{
        char sc = (next(mp.begin()))->first;
        mp[sc]--;
        string t;
        t+=sc;
        for(auto p:mp){
            while(p.second){
                t+=p.first;
                p.second--;
            }
        }
        cout << t << endl;
    }
    return;
}

int main(){
    int t = 1;
    //cin >> t;
    while(t--){
        test_case();
    }
    return 0;
}