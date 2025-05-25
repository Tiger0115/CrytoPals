#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myFunctions.h"

/*Compile and Run Commands From Challenge - 
 *
 *gcc challenge2.c -o xor
 *./xor 1c0111001f010100061a024b53535009181c 686974207468652062756c6c277320657965
 *
 *Expected Output - 
 *746865206b696420646f6e277420706c6179 
*/

/*challenge2.c - takes 2 arguments in hexadecimal format and prints their xor in the same format
 *
 *@arguments - 2 strings in hexadecimal format
 *@prints - xor of the 2 strings in hexadecimal format
*/
int main(int argc, char* argv[])
{
    if(argc!=3)
    {
        printf("Error in Argument count \n");
        return -1;
    }

    char* result=xorOfHexadecimal(argv[1], argv[2]);

    printf("%s \n", result);

    free(result);
}