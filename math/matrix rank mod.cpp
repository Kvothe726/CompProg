//Rouché–Capelli theorem
int rank(int M, int N, int[][] a, int[] b, int p){
    // M equations, N variables
    int ans = 0;

    boolean used[] = new boolean[M];

    // Using Gauss-Jordan in [ A : b ] to make it in row-echellon form.
    // So that we can find the rank. We also need to make sure that the
    // rank of [ A ] is equal to the rank of [A : b], else there are
    // no solutions
    for (int j=0; j<N; j++){
        int i = 0;
        while ( (i < M) && (used[i] || (a[i][j] == 0) ) ) {
            i++;
        }
        if(i == M) continue;
        ans++;
        used[i] = true;
        for (int k=0; k<M; k++) if(!used[k]){
            // Find a value of coef equal to (-a[k][j] / a[i][j]);
            // we can just try 0,1,..,p-1 until we find one.
            int coef = 0;
            while ( (a[i][j] * coef + a[k][j]) % p != 0) {
                coef++;
            }
            for (int l=0; l<N; l++) {
                 a[k][l] = (a[k][l] + a[i][l] * coef) % p;
            }
            b[k] = (b[k] + b[i] * coef) % p;
        }
    }

    // If rank of [A] is not equal to the rank of [A : b]
    for (int i=0; i<M; i++) {
         if(!used[i] && b[i] != 0) {
              return -1;
         }
    }

    return ans;
}
