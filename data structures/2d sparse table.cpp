#include <bits/stdc++.h>
#define inf 1000000010

using namespace std;

const int N = 510 , LOG = 10;   // size of the array

int n,m,arr[N][N];
int st[N][N][LOG][LOG] , lg[N];

void build(){
    lg[1] = 0;
    for(int i = 2;i<N;i++){
        lg[i] = lg[i - 1];
        if((1 << (lg[i] + 1)) == i)
            lg[i]++;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            st[i][j][0][0] = arr[i][j];
        }
    }

    for(int k = 1;k < LOG;k++){
        for(int i=0;i + (1 << k) <= n;i++){
            for(int j=0;j<m;j++){
                st[i][j][k][0] = max(st[i][j][k - 1][0] , st[i + (1 << (k - 1))][j][k - 1][0]);
            }
        }
    }
    for(int l = 1;l < LOG;l++){
        for(int k = 0;k < LOG;k++){
            for(int i=0;i+(1 << k) <= n;i++){
                for(int j = 0;j + (1 << l) <= m;j++){
                    st[i][j][k][l] = max(st[i][j][k][l - 1] , st[i][j + (1 << (l - 1))][k][l-1]);
                }
            }
        }
    }
}

inline int getmax(int r1,int c1,int r2,int c2){
    if(r2 < r1 || c2 < c1 || r1 < 0 || r2 >= n || c1 < 0 || c2 >= m) return -inf;
    int a = lg[(r2 - r1) + 1];
    int b = lg[(c2 - c1) + 1];
    return max(max(st[r1][c1][a][b] , st[r2 - (1 << a) + 1][c1][a][b]) , max(st[r1][c2 - (1 << b) + 1][a][b] , st[r2 - (1 << a) + 1][c2 - (1 << b) + 1][a][b]));
}


int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> arr[i][j];
        }
    }
    build();
    int q; cin >> q;
    while(q--){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--,y1--,x2--,y2--;
        cout << getmax(x1,y1,x2,y2) << endl;
    }
    return 0;
}
