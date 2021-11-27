// remember lines that are added should be in decreasing order of slope.
// (look the lines only at the 1st and 4th quadrants to understand decreasing slope).
struct line{
    ll m;
    ll c;
};

class convexhull{
public:
    int n=0;
    vector <ll> st;
    vector <line> lines;
    // need an initial line to set the starting point of that line
    convexhull(line a){
        st.push_back(0);
        lines.push_back(a);
        n++;
    }
    ll get(line &a, ll x){
        return a.m*x+a.c;
    }
    bool isgreat(line &a, line &b, ll x){
        return a.m*x+a.c >= b.m*x+b.c;
    }
    getceil(ll num, ll den){
        if(num == 0){
            return 0;
        }
        assert(den!=0);

        int sign = (num/abs(num))*(den/abs(den));
        num = abs(num);
        den = abs(den);

        if(sign == 1){
            return (num+den-1)/den;
        }
        else{
            return -(num/den);
        }
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
            if(a.m == la.m){
                return;
            }
            xint = getceil((la.c-a.c),(a.m-la.m));
        }
        st.push_back(xint);
        lines.push_back(a);
        n++;
    }
    ll getmin(ll x){
        auto it = upper_bound(st.begin(),st.end(),x)-st.begin()-1;
        return get(lines[it],x);
    }
};
