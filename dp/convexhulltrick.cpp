struct line{
    int m;
    ll c;
};

class convexhull{
public:
    int n=0;
    vector <ll> st;
    vector <line> lines;
    convexhull(line a){
        st.push_back(0);
        lines.push_back(a);
        n++;
    }
    ll get(line &a, ll x){
        return 1ll*a.m*x+a.c;
    }
    ll getceil(ll p, int q){
        p=abs(p),q=abs(q);
        return (p+q-1)/q;
    }
    bool isgreat(line &a, line &b, ll x){
        return x>=getceil(b.c-a.c,a.m-b.m);

    }
    void update(line a){
        for(int i=n-1;i>=0;i--){
            if(isgreat(lines[i],a,st[i])){
                st.pop_back();
                lines.pop_back();
                n--;
            }
            else{
                break;
            }
        }
        ll xint=0;
        if(lines.size()){
            line la = lines.back();
            xint = getceil((la.c-a.c),(a.m-la.m));
        }
        st.push_back(xint);
        lines.push_back(a);
        n++;
    }
    ll getmin(int x){
        auto it = upper_bound(st.begin(),st.end(),x)-st.begin()-1;
        return get(lines[it],x);
    }
};
