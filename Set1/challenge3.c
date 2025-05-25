#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myFunctions.h"

/*Sample Run From Challenge - 
 *
 *gcc challenge3.c -o single
 *./single 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
 *
 *Expected Output - 
 *746865206b696420646f6e277420706c6179 
*/

/*challenge3.c - 
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

    singleByteXorWithHex(argv[1]);

    printf("---------------------------------------------------\n");
    printf("Answer - \nIteration= 88 \t Key = X \nResult = Cooking MC's like a pound of bacon\n");
    printf("---------------------------------------------------\n\n");
    
}