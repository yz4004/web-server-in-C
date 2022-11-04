#include <stdio.h>
#include "prime.h"
#include "gcd.h"
int main()
{
    int x,y ;

    printf("please input two positive integers: ");
    scanf("%d%d", &x,&y );
    printf("You typed in %d and %d\n", x, y);
    printf("The average is %f\n",( ((float) x)+ ((float) y ) )/2);  
        
    if(whether_prime(x) == 1) 
        printf("%d is prime\n", x);
    else
        printf("%d is not prime\n",x);
    
    if(whether_prime(y) == 1)
        printf("%d is prime\n", y);
    else
        printf("%d is not prime\n", y);
    
    printf("The gcd of %d, %d is %d\n", x,y,gcd(x,y));
    

    return 0;
}
