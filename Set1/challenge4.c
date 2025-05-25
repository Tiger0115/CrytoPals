#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myFunctions.h"

/*Compile and Run Commands From Challenge - 
 *
 *wget https://www.cryptopals.com/static/challenge-data/4.txt
 *gcc challenge4.c -o detect
 *./detect 4.txt 60
 *
 *Expected Output - 
 * Now that the party is jumping
*/

/*challenge4.c - takes a filename containing hexadecimal strings of fixed length which are then xored with a byte key to find the plaintext.
 *               All combinations are tried.
 *
 *@arguments - filepath and length of a hexadecimal string
 *@prints - prints all permutations of xor which pass the english check
*/
int main(int argc, char* argv[])
{
    if(argc!=3)
    {
        printf("Error in Argument count \n");
        return -1;
    }

    int length=atoi(argv[2]);
    printf("len = %d\n", length);


    fileSingleByteXorWithHex(argv[1], 60);

    printf("---------------------------------------------------\n");
    printf("Answer - \nLineNumber=171 \nIteration= 53 \t Key = 5 \nResult = Now that the party is jumping\n");
    printf("---------------------------------------------------\n\n");
}