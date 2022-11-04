#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort_integer_array(int *begin, int *end, int ascending);

int main(){

    srandom(time(NULL));

    // read array size from user
    int size;
    printf("Please input size here: ");
    scanf("%d", &size);

    // create array
    // int a[size];
    
    int *a = (int *) malloc( sizeof(int) * size);
    if (a == NULL) {
         perror("malloc returned NULL");
         exit(1);
    }
    int r;
    for(int i=0; i<size; i++){

        r = (int) (random()%100);
        *(a+i) = r; 
        //printf("%d %d\n", r, *(a+i));
    }

    int *b =(int *)  malloc( sizeof(int) * size);
    if (b == NULL) {
         perror("malloc returned NULL");
         exit(1);
    }
    for(int i=0; i<size; i++){

        *(b+i) = *(a+i);
    }

    int *c = (int *) malloc( sizeof(int)* size);
    if (c == NULL) {
         perror("malloc returned NULL");
         exit(1);
    }
    for(int i=0; i<=size; i++){
        *(c+i) = *(a+i);
    }

    sort_integer_array(b, b+size, 1); // end b + size - 1

    sort_integer_array(c, c+size, 0);


    printf("original:");
    for(int i=0; i<size; i++){
        printf("%d  ", a[i]);
    }
    printf("\n");
        
    printf("ascending: ");
    for(int i=0; i<size; i++){
        printf("%d  ", b[i]);
    }
    printf("\n");

    printf("descending: ");
    for(int i=0; i<size; i++){
        printf("%d  ", c[i]);
    }
    printf("\n");

    free(a);
    free(b);
    free(c);

    return 0;
}



 /* This function sorts an integer array.
 
 begin points to the 1st element of the array.
 end points to ONE PAST the last element of the array.
 If ascending is 1, the array will be sorted in ascending order.
 If ascending is 0, the array will be sorted in descending order.
 */
 void sort_integer_array(int *begin, int *end, int ascending) 
 {
 /* In here, you will call your real sorting function (your own
 * or the qsort()). Basically, I want to make sure that you
 * know how to translate the begin/end parameter to whatever
 * is required for your sorting function.
 *
 *
 * Insertion Sort. 
 * From the lecture note of COMSW 3134
 *
 */
 
    
    int index = 1;
    int temp;
    int current;
    if( ascending){

        while((begin+index) != end ){  // index < size

            temp =*(begin+index);
            // move current/curser to the place i, where a[i] < a[index] and a[i+1] > a[index]
            current = index;
            while((current >0) &  (*(begin + current-1) > temp)){
                // not index - 1 in last row, but compare a[current-1] in condition, and use lazy &
                *(begin + current) = *(begin + current-1); // put a[current-1] 1 digit back
                current--;                 // current move forward
            }
        *(begin + current) = temp;
        index++;
        }
    }else{
        while((begin+index) != end){
            temp = *(begin + index);
            // move current/curser to the place i, where a[i] < a[index] and a[i+1] > a[index]
            current = index;
            while((current >0) &  (*(begin + current-1) < temp)){
                // not index - 1 in last row, but compare a[current-1] in condition, and use lazy &
                *(begin + current) = *(begin + current-1); // put a[current-1] 1 digit back
                current--;                 // current move forward
            }
            *(begin + current) = temp;
            index++;
   
        }
    }

}
