#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
function checkHexCanBeConvertedToBase64 -checks the length of input and verifies if it is divisible by 3 so that it can be converted to base64

you can add more sanitation checks to check if it is hexadecimal or not.
*/
int checkHexCanBeConvertedToBase64(char* input)
{
    int len=strlen(input);

    if(len%3==0)
        return 1;
    else
        return -1;    
}

int getLength(char* input)
{
    return strlen(input);
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

int getmax(int one, int two)
{
    if(one>two)
        return one;
    else
        return two; 
}


char* xorOfBinary(char* bin1, char* bin2)
{
    int len1=getLength(bin1);
    int len2=getLength(bin2);

    char* result=malloc(getmax(len1,len2)+1);
    result[getmax(len1,len2)]='\0';

    for(int i=0;i<getmax(len1,len2);i++)
    {
        if(i<len1 && i<len2)
        {
            if(bin1[i]==bin2[i])
            {
                result[i]='0';
            }

            else
            {
                result[i]='1';
            }
        }
        else if(i>=len1 && i<len2)
        {
            //do nothing
        }

        else if(i<len1 && i>=len2)
        {
            //do nothing
        }
        else
        {
            break;
        }
    }

    return result;
}



char* binaryToHexadecimal(char* binary)
{
    int len=strlen(binary);

    char encoding_table[]= {'0', '1', '2', '3', '4', '5',
                            '6', '7', '8', '9', 'a',
                            'b', 'c', 'd', 'e', 'f' };

    int output_len = (len + 3) / 4;
    char* hexResult = malloc(output_len + 1);

    int sum=0;
    int index=0;

    for(int i=0;i<len;i+=4)
    {
        int sum=0;
        for(int j=3;j>=0;j--)
        {
            if((i+j)<len && binary[i+j]=='1')
            {
                sum+=(1<<(3-j));
            }
        }

        hexResult[index]=encoding_table[sum];
        index++;  

    }

    hexResult[output_len]='\0';
    return hexResult;
}


char* binaryToAscii(char* binary)
{
    int len=strlen(binary);

    
    int output_len = (len + 7) / 8;
    char* binaryResult = malloc(output_len + 1);

    
    int index=0;

    for(int i=0;i<len;i+=8)
    {
        int sum=0;
        for(int j=7;j>=0;j--)
        {
            if((i+j)<len && binary[i+j]=='1')
            {
                sum+=(1<<(7-j));
            }
        }

        binaryResult[index]=(char) sum;
        index++;  

    }

    binaryResult[output_len]='\0';
    return binaryResult;
}


char* asciiToBinary(char* input)
{
    int len=strlen(input);

    
    
    char* binaryResult = malloc((len*8) + 1);

    for(int i=0;i<len;i++)
    {
       int num=(int)input[i];

       for (int j = 7; j >= 0; j--)
        {
            binaryResult[i * 8 + (7 - j)] = (num & (1 << j)) ? '1' : '0';
        }

    }

    binaryResult[len*8]='\0';
    return binaryResult;
}