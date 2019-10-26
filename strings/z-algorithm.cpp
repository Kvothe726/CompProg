class zalgo {
public:
    string s;
    int n;
    int z[nmax];
    zalgo(string p) {
        memset(z, 0, sizeof(z));
        s = p;
        n = p.size();
        computez();
    }
    void computez() {
        z[0]=n;
        int L = 0, R = 0;
        for (int i = 1; i < n; i++) {
            if (i > R) {
                L = R = i;
                while (R < n && s[R - L] == s[R]) R++;
                z[i] = R - L; R--;
            }
            else {
                int k = i - L;
                if (z[k] < R - i + 1) z[i] = z[k];
                else {
                    L = i;
                    while (R < n && s[R - L] == s[R]) R++;
                    z[i] = R - L; R--;
                }
            }
        }
    }
    int operator[](int ind){
        return z[ind];
    }
};
