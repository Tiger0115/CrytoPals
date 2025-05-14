#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myFunctions.h"

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        printf("Error in Argument count \n");
        return -1;
    }


    char* binaryString= hexadecimalToBinary(argv[1]);
    int stringLen = getLength(argv[1]);

    char* xorString= malloc(stringLen+1);

    for(int i=0;i<256;i++)
    {
        for(int j=0;j<stringLen;j++)
        {
            xorString[j]=(char)i;
        }

        printf("%d = %s \n",i, binaryToAscii(xorOfBinary(binaryString, asciiToBinary(xorString))));
        printf("------------------------\n");
    }

    for(int j=0;j<stringLen;j++)
    {
        xorString[j]=(char)88;
    }

    printf("88 = %s \n", binaryToAscii(xorOfBinary(binaryString, asciiToBinary(xorString))));
    printf("Key = %s \n", xorString);
}
