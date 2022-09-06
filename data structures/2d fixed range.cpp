void solverow(vector<int> &a, int k){
    int n = a.size();
    vector<int> ta(n);
    deque<int> q;

    for(int i=0;i<k-1;i++){
        while(q.size() && a[q.front()]>=a[i]){
            q.pop_front();
        }
        q.push_front(i);
    }

    for(int i=0;i<=n-k;i++){
        while(q.size() && a[q.front()]>=a[i+k-1]){
            q.pop_front();
        }
        q.push_front(i+k-1);

        if(q.back()<i){
            q.pop_back();
        }
        ta[i] = a[q.back()];
    }
    for(int i=0;i<=n-k;i++){
        a[i] = ta[i];
    }
}

void transpose(vector<vector<int>> &a){
    int n = a.size(), m = a[0].size();

    vector<vector<int>> t(m,vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            t[j][i] = a[i][j];
        }
    }

    a = t;
    return;
}

void premin(vector<vector<int>> &a, int kn, int km){
    int n = a.size(), m = a[0].size();
    for(int i=0;i<n;i++){
        solverow(a[i], km);
    }

    transpose(a);
    for(int i=0;i<m;i++){
        solverow(a[i],kn);
    }
    transpose(a);

    // resize a
    for(int i=0;i<n;i++){
        a[i].resize(m-km+1);
    }
    a.resize(n-kn+1);
    return;
}