#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
function checkInput -checks the length of input and verifies if it is divisible by 3 so that it can be converted to base64

you can add more sanitation checks to check if it is hexadecimal or not.
*/
int checkInput(char* input)
{
    int len=strlen(input);

    if(len%3==0)
        return 1;
    else
        return -1;    
}


/*
function hexadecimalToBinary - converts a hexadecimal input to binary

feel free to optimize it, there is a print statement at the end if you want to print the binary string
*/
char* hexadecimalToBinary(char* input)
{
    int len=strlen(input);  
    // printf("%d \n", len);

    char* binary=malloc((4*len)+1);
    binary[4*len]='\0';

    int i=0;
    while(i<len)
    {
        switch(input[i])
        {
            case '0':   binary[i*4]='0';
                        binary[(i*4)+1]='0';
                        binary[(i*4)+2]='0';
                        binary[(i*4)+3]='0';
                        break;
            
            case '1':   binary[i*4]='0';
                        binary[(i*4)+1]='0';
                        binary[(i*4)+2]='0';
                        binary[(i*4)+3]='1';
                        break;

            case '2':   binary[i*4]='0';
                        binary[(i*4)+1]='0';
                        binary[(i*4)+2]='1';
                        binary[(i*4)+3]='0';
                        break;
                        
            case '3':   binary[i*4]='0';
                        binary[(i*4)+1]='0';
                        binary[(i*4)+2]='1';
                        binary[(i*4)+3]='1';
                        break;                        
            
            case '4':   binary[i*4]='0';
                        binary[(i*4)+1]='1';
                        binary[(i*4)+2]='0';
                        binary[(i*4)+3]='0';
                        break;

            case '5':   binary[i*4]='0';
                        binary[(i*4)+1]='1';
                        binary[(i*4)+2]='0';
                        binary[(i*4)+3]='1';
                        break;
                        
            case '6':   binary[i*4]='0';
                        binary[(i*4)+1]='1';
                        binary[(i*4)+2]='1';
                        binary[(i*4)+3]='0';
                        break;                
            
            case '7':   binary[i*4]='0';
                        binary[(i*4)+1]='1';
                        binary[(i*4)+2]='1';
                        binary[(i*4)+3]='1';
                        break;

            case '8':   binary[i*4]='1';
                        binary[(i*4)+1]='0';
                        binary[(i*4)+2]='0';
                        binary[(i*4)+3]='0';
                        break;
                        
            case '9':   binary[i*4]='1';
                        binary[(i*4)+1]='0';
                        binary[(i*4)+2]='0';
                        binary[(i*4)+3]='1';
                        break;                        
            
            case 'a':   binary[i*4]='1';
                        binary[(i*4)+1]='0';
                        binary[(i*4)+2]='1';
                        binary[(i*4)+3]='0';
                        break;

            case 'b':   binary[i*4]='1';
                        binary[(i*4)+1]='0';
                        binary[(i*4)+2]='1';
                        binary[(i*4)+3]='1';
                        break;
                        
            case 'c':   binary[i*4]='1';
                        binary[(i*4)+1]='1';
                        binary[(i*4)+2]='0';
                        binary[(i*4)+3]='0';
                        break;

            case 'd':   binary[i*4]='1';
                        binary[(i*4)+1]='1';
                        binary[(i*4)+2]='0';
                        binary[(i*4)+3]='1';
                        break;

            case 'e':   binary[i*4]='1';
                        binary[(i*4)+1]='1';
                        binary[(i*4)+2]='1';
                        binary[(i*4)+3]='0';
                        break;
                        
            case 'f':   binary[i*4]='1';
                        binary[(i*4)+1]='1';
                        binary[(i*4)+2]='1';
                        binary[(i*4)+3]='1';
                        break;
        }


        i++;
    }

    // printf("%s \n", binary);
    return binary;

}

char* binaryToBase64(char* binary)
{
    int len=strlen(binary);

    char encoding_table[]= {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                            'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                            'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                            'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                            'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                            'w', 'x', 'y', 'z', '0', '1', '2', '3',
                            '4', '5', '6', '7', '8', '9', '+', '/'};

    int output_len = (len + 5) / 6;
    char* base64 = malloc(output_len + 1);

    int sum=0;
    int index=0;

    for(int i=0;i<len;i+=6)
    {
        int sum=0;
        for(int j=5;j>=0;j--)
        {
            if((i+j)<len && binary[i+j]=='1')
            {
                sum+=(1<<(5-j));
            }
        }

        base64[index]=encoding_table[sum];
        index++;  

    }

    return base64;
}


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

    if(checkInput(argv[1])!=1)
    {
        printf("Error - Unlcean input \n");
        return -1;
    }

    char* binary=hexadecimalToBinary(argv[1]);

    char* base64=binaryToBase64(binary);

    printf("%s \n", base64);

    free(base64);
    free(binary);
}