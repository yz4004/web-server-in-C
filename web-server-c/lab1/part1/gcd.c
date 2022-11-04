
#include "gcd.h"
//
// default input x < y
int gcd(int x, int y)
{
    if( y%x == 0)
        return x;
    else
        return gcd( y%x, x);
}

