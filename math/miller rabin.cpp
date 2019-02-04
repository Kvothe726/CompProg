static int (*rand_func)(void) = rand;

static int rand_max = RAND_MAX;

static uint64_t pow_mod(uint64_t a, uint64_t x, uint64_t n)
{
  uint64_t r=1;

  while ( x ) {
    if ( (x & 1) == 1 )
      //r = (__int128_t)a*r % n; // Slow
      r = a*r % n;

    x >>= 1;
    //a = (__int128_t)a*a % n; // SLow
    a = a*a % n;
  }

  return r;
}
static uint64_t rand_between(uint64_t a, uint64_t b)
{
  // Assume rand_func() is 32 bits
  uint64_t r = (static_cast<uint64_t>(rand_func())<<32) | rand_func();
  return a + (uint64_t)((double)(b-a+1)*r/(UINT64_MAX+1.0));
}
bool isprime(uint64_t n, int k=5)
{
  if ( n==2 || n==3 ) return true;
  if ( n<=1 || !(n & 1) ) return false;

  int s = 0;
  for ( uint64_t m = n-1; !(m & 1); ++s, m >>= 1 )
    ; // loop

  uint64_t d = (n-1) / (1<<s);

  for ( int i = 0; i < k; ++i ) {
    uint64_t a = rand_between(2, n-2);
    uint64_t x = pow_mod(a,d,n);

    if ( x == 1 || x == n-1 )
      continue;

    for ( int r = 1; r <= s-1; ++r ) {
      x = pow_mod(x, 2, n);
      if ( x == 1 ) return false;
      if ( x == n - 1 ) goto LOOP;
    }

    return false;
LOOP:
    continue;
  }

  // n is *probably* prime
  return true;
}
void setrand(int (*pf)(void), const int rmax)
{
  if ( pf != NULL ) {
    rand_func = pf;
    rand_max = rmax;
  } else {
    rand_func = rand;
    rand_max = RAND_MAX;
  }
}

bool check(uint64_t num){           // just a safe check after isprime(miller rabin)
    for(int i=2;i*i<=num;i++){
        if(num%i==0)
            return false;
    }
    return true;
}
