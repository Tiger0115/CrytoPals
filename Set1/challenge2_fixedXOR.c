#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myFunctions.h"

int main(int argc, char* argv[])
{
    if(argc!=3)
    {
        printf("Error in Argument count \n");
        return -1;
    }


    char* hexResult=xorOfHexadecimal(argv[1],argv[2]);
    printf("%s \n", hexResult);

    free(hexResult);


    // char* binary1=hexadecimalToBinary(argv[1]);
    // char* binary2=hexadecimalToBinary(argv[2]);

    // printf("%s \n", binary1);
    // printf("%s \n", binary2);

    // char* binaryResult=xorOfBinary(binary1, binary2);

    // printf("%s \n", binaryResult);

    // char* hexResult=binaryToHexadecimal(binaryResult);

    // printf("%s \n", hexResult);

    // free(binary1);
    // free(binary2);
    // free(binaryResult);
    // free(hexResult);

}