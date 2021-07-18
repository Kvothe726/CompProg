// generating a random sequence of distinct elements
#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);

    cout << rnd.next("[a-c]{12}") << endl;

    return 0;
}
