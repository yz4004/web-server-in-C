#include "prime.h"
#include <math.h>

int  whether_prime(int x)
{
    if(x == 1) return 0;
    float y = (float) x;
    y = sqrt(y);

    for(int i=2; i<=y; i++){
        if( x%i == 0)  return 0;
        // 0 indicates x is not prime
    }
    return 1;
}    
