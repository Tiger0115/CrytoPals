#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myFunctions.h"

/*Compile and Run Commands From Challenge - 
 *
 *gcc challenge5.c -o five
 *./five
 *
 *Expected Output - 
 * 
*/

/*challenge4.c - 
 *
 *@arguments - 
 *@prints - 
*/
int main(int argc, char* argv[])
{
    if(argc!=4)
    {
        printf("Error in Argument count \n");
        return -1;
    }

    int length=atoi(argv[3]);

    fileRepeatingKeyXorByte(argv[1], length, argv[2]);
}