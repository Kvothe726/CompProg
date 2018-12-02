template <class T>
void covbin(vector<int> &a, T num ){
    while(num > 0){
        a.pb(num%2);
        num/=2;
    }
    return;
}
