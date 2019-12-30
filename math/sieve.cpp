int prime[nmax];
vector <int> primes;

void sieve()
{
    for(int i=0;i<nmax;i++) {
        prime[i] = i;
    }
    for (int p=2; p*p<=(nmax-1); p++)
    {
        if (prime[p] == p)
        {
            for (int i=p*p; i<=(nmax-1); i += p)
                prime[i] = p;
        }
    }
    for(int i=2;i<nmax;i++){
        if(prime[i]==i){
            primes.push_back(i);
        }
    }
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

vector <int> prime;
bool is_composite[nmax];
int phi[nmax];

void sieve () {
	std::fill (is_composite, is_composite + nmax, false);
	phi[1] = 1;
	for (int i = 2; i < nmax; ++i) {
		if (!is_composite[i]) {
			prime.push_back (i);
			phi[i] = i - 1;					//i is prime
		}
		for (int j = 0; j < prime.size () && i * prime[j] < nmax; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];	//prime[j] divides i
				break;
			} else {
				phi[i * prime[j]] = phi[i] * phi[prime[j]];	//prime[j] does not divide i
			}
		}
	}
}
