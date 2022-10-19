#include "jngen.h"
using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    parseArgs(argc, argv);

    cout << 1 << endl;
    int n = rnd.next(1,4), e = rnd.next(0,10);
    cout << n << " " << e << endl;
    for(int i=0;i<n;i++){
        cout << rnd.next(0,5) << " " << rnd.next(0,5) << " " << rnd.next(1,10) << endl;
    }
    return 0;
}