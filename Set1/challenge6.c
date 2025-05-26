#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myFunctions.h"

/*Compile and Run Commands From Challenge - 
 *
 *gcc challenge6.c -o break
 *./break
 *
 *Expected Output - 
 * 
*/

/*challenge6.c -
 *
 *@arguments - 
 *@prints - 
*/
int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        printf("Error in Argument count \n");
        return -1;
    }

    unsigned char* input1="this is a test";
    unsigned char* input2="wokka wokka!!!";
    printf("%d\n", hammingDistanceByte(input1, input2));

    free(input1);
    free(input2);


}   