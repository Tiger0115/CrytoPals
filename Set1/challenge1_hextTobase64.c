#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "myFunctions.h"

/*
hextobase64.c - converts the given hexadecimal input to base64 type

input - a string of hexadecimal in command line
output - a string in base 64 format
*/
int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        printf("Error in Argument count \n");
        return -1;
    }

    if(checkHexCanBeConvertedToBase64(argv[1])!=1)
    {
        printf("Error - hex is not appropriate size \n");
        return -1;
    }

    char* base64=hexadecimaltoBase64(argv[1]);

    printf("%s \n", base64);

    free(base64);
}