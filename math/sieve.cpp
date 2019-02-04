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
