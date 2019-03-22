int prime[MAXV];
vector <int> primes;

void sieve()
{
    F(i,1,MAXV)
        prime[i]=i;

    for (int p=2; p*p<=(MAXV-1); p++)
    {
        if (prime[p] == p)
        {
            for (int i=p*p; i<=(MAXV-1); i += p)
                prime[i] = p;
        }
    }
    F(i,2,MAXV){
        if(prime[i]==i){
            primes.pb(i);
        }
    }
    return;
}


int mob[nmax];
int prime[nmax];

void mobsieve(){
    for(int i=2;i<nmax;i++){
        prime[i]=1;
        mob[i]=1;
    }
    mob[1]=1;
    for(int i=2;i<nmax;i++){
        if(prime[i]){
            mob[i]=-1;
            for(int j=i;j<nmax;j+=i){
                prime[j]=0;
                int k=j/i;
                if(k%i!=0){
                    mob[j]=mob[i]*mob[k];
                }
                else{
                    mob[j]=0;
                }
            }
        }

    }

    return;
}