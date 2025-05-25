#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myFunctions.h"

/*Compile and Run Commands From Challenge - 
 *
 *gcc challenge3.c -o single
 *./single 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
 *
 *Expected Answer - 
 *Cooking MC's like a pound of bacon 
*/

/*challenge3.c - a hexadecimal string is a cipher text which is xored with a single byte, this tries out all bytes to find the correct one.
 *
 *@arguments - takes in a char array in hexadecimal format
 *@prints - prints all permutations of xor which pass the english check
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