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

    int lineSize= atoi(argv[2]);
    printProbableKeyOfSameByteFile(argv[1], lineSize);


    printf("Answer is Line 171 (if lines are 1 indexed) \nPlaintext = Now that the party is jumping \nKey = 555555555555555555555555555555555555555555555555555555555555 \n");
    
}