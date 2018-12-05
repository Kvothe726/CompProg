void ncrDP(){
    ncr[0][0]=1;
    for(int i=1;i<1005;i++){
        ncr[i][0]=1;
        for(int j=1;j<1005;j++){
            ncr[i][j]=(ncr[i-1][j-1]+ncr[i-1][j])%mod;
        }
    }
    return;
}
