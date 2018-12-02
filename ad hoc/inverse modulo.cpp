template <typename T>
void EE(T a, T b, T& x, T& y)
{
    if(a%b == 0)
    {
        x=0;
        y=1;
        return;
    }
    EE(b,a%b,x,y);
    T temp = x;
    x = y;
    y = temp - y*(a/b);
}

template <typename T>
T inverse(T a, T m)
{
    T x,y;
    EE(a,m,x,y);
    if(x<0) x += m;
    return x;
}

