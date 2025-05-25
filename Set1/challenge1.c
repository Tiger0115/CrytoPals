#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myFunctions.h"

/*Compile and Run Commands From Challenge - 
*
*gcc challenge1.c -o hex
*./hex 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
*
*Expected Output - 
*SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t 
*/

/*challenge1.c - converts the given hexadecimal input to base64 formate
 *
 *@arguments - a string of hexadecimal in command line
 *@prints - a string in base 64 format
*/
int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        printf("Error in Argument count \n");
        return -1;
    }

    char* base64=hexadecimalToBase64(argv[1]);

    printf("%s \n", base64);

    free(base64);
}