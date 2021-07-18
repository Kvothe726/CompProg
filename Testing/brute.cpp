#include <bits/stdc++.h>

using namespace std;

int main(){
    string s; cin >> s;
    int n = s.size();
    sort(s.begin(),s.end());
    pair<int,string> ans(INT_MAX,"");
    do{
        int mx = 0;
        for(int i=1;i<n;i++){
            int cur = 0, ind = i;
            for(int j=0;j<n;j++){
                if(s[ind]!=s[j]){
                    break;
                }
                cur++;
                ind++;
            }
            mx = max(mx, cur);
        }
        ans = min(ans, make_pair(mx, s));
    }
    while(next_permutation(s.begin(),s.end()));

    //<< ans.first << " " 
    cout << ans.second << endl;
}