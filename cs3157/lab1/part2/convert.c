#include <stdio.h>

int convert_binary(int x);

int convert(){    
    int x;    
    scanf("%d",&x);
    printf("signed dec:   %d\n", x);
    printf("unsigned dec: %u\n", x);
    printf("hex:          %x\n", x);
    convert_binary(x);
    return 0; 
}

int convert_binary(int x){    

    

    char output[39] ={0};
    int i;
    int mask = 1;	
    for (i=38; i>-1; i--) {  
        if( ((i+1)%5 == 0) && i != 0 ){
            output[i] = ' ';
        }else{

            if(x& mask){
                output[i] = '1';
            }else{
           
                output[i] = '0';
            }
            mask <<= 1;
        }
                
                
    } 
    printf("binary:       %s\n", output);

    return 0;
}

int main()
{
    convert();

    return 0;
}

