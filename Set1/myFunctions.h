#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

char* hexadecimaltoBase64(char* input)
{
    char* binary=hexadecimalToBinary(input);
    char* base64=binaryToBase64(binary);

    free(binary);

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

    int min_len = len1 < len2 ? len1 : len2;
    char* result = malloc(min_len + 1);
    for (int i = 0; i < min_len; i++) 
    {
        result[i] = bin1[i] == bin2[i] ? '0' : '1';
    }

    result[min_len] = '\0';
    

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

char* xorOfHexadecimal(char* input1, char* input2)
{
    char* bin1= hexadecimalToBinary(input1);
    char* bin2= hexadecimalToBinary(input2);

    char* binResult=xorOfBinary(bin1, bin2);
    char* hexResult= binaryToHexadecimal(binResult);

    free(bin1);
    free(bin2);
    free(binResult);

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

// int englishCheck(char* input)
// {
//     int len=strlen(input);

//     for(int i=0;i<len;i++)
//     {
//         // printf("%d = %c %d \n", i, input[i], (int)input[i]);
//         if ((unsigned char)input[i] < 32 || (unsigned char)input[i] > 126 ) 
//         {
//             return -1;
//         }
//     }

//     return 1;
// }


int englishCheck(char* input)
{
    int len = strlen(input);
    int printable = 0;
    int total = 0;

    for(int i = 0; i < len; i++)
    {
        char c = input[i];
        total++;

        // Acceptable characters:
        if (isalpha(c) || isdigit(c) || isspace(c) || ispunct(c))
        {
            printable++;
        }
        else
        {
            // Reject control characters and non-printables
            if ((unsigned char)c < 32 || (unsigned char)c > 126)
                return 0;
        }
    }

    // Require that a high percentage of characters are printable
    return (printable >= total * 0.95) ? 1 : 0;
}

void printProbableKeyOfSameByte(char* binaryCiphertext, int keyLength )
{
    char* key=malloc(keyLength+1);
    key[keyLength]='\0';

    for(int i=0;i<256;i++)
    {
        for(int j=0;j<keyLength;j++)
        {
            key[j]=(char)i;
        }

        char* xorBinary=asciiToBinary(key);
        char* xorResultBinary=xorOfBinary(binaryCiphertext, xorBinary);
        char* asciiResult= binaryToAscii(xorResultBinary);

        if(englishCheck(asciiResult))
        {
            printf("Plaintext = %s \n", asciiResult);
            printf("Key = %s \n", key);
            printf("------------------------\n");
        }

        free(xorBinary);
        free(xorResultBinary);
        free(asciiResult);
    }
    free(key);
}

void printProbableKeyOfSameByteFile(char* filename, int lineSize)
{
    FILE* fptr=fopen(filename, "r");
    if (!fptr) {
        perror("Error opening file");
        return;
    }

    char* line=malloc(lineSize+4);

    
    int i =0;
    
    while(fgets(line, lineSize+4, fptr))
    {
        line[strcspn(line, "\n")] = '\0'; 

        char* binary = hexadecimalToBinary(line);       

        printf("Line Number = %d \n", (i+1));
        printProbableKeyOfSameByte(binary, lineSize);
        printf("\n\n");        
        i++;

        free(binary);
               
        
    }

    fclose(fptr);
    free(line);
}

char* binaryToHex(char* binary) 
{
    int len = strlen(binary);

    // Make sure length is a multiple of 4 by padding with leading 0s
    int paddedLen = len;
    int pad = (4 - (len % 4)) % 4;
    paddedLen += pad;

    char* paddedBinary = (char*)malloc(paddedLen + 1);
    for (int i = 0; i < pad; i++) {
        paddedBinary[i] = '0';
    }
    strcpy(paddedBinary + pad, binary);
    paddedBinary[paddedLen] = '\0';

    // Allocate memory for hex string
    char* hex = (char*)malloc(paddedLen / 4 + 1);

    for (int i = 0; i < paddedLen; i += 4) {
        int value = 0;
        for (int j = 0; j < 4; j++) {
            value = value * 2 + (paddedBinary[i + j] - '0');
        }
        if (value < 10)
            hex[i / 4] = '0' + value;
        else
            hex[i / 4] = 'a' + (value - 10);
    }

    hex[paddedLen / 4] = '\0';
    free(paddedBinary);
    return hex;
}

int base64CharToValue(char c) {
    if ('A' <= c && c <= 'Z') return c - 'A';
    if ('a' <= c && c <= 'z') return c - 'a' + 26;
    if ('0' <= c && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    if (c == '=') return 0; // Padding
    return -1; // Invalid character
}

char* base64ToBinary(char* input) {
    int len = strlen(input);
    char* binary = malloc(len * 6 + 1); // 6 bits per base64 char
    if (!binary) {
        perror("malloc failed");
        exit(1);
    }

    binary[0] = '\0'; // initialize as empty string

    for (int i = 0; i < len; i++) {
        int val = base64CharToValue(input[i]);
        if (val == -1) continue; // skip invalid characters

        for (int bit = 5; bit >= 0; bit--) {
            char bitChar = ((val >> bit) & 1) ? '1' : '0';
            strncat(binary, &bitChar, 1);
        }
    }

    return binary;
}

int computeHammingDistanceOfBinary(char* input1, char* input2)
{
    // if(strlen(input1)!= strlen(input2))
    //     return -1;

    int count=0;

    for(int i=0;i<strlen(input1); i++)
    {
        if(input1[i]!=input2[i])
            count++;
    }

    return count;
}

int findKeysizeWithSmallestHammingDistance(char* filename, int minKeyLength, int maxKeyLength)
{
    double min=10000.0;

    int minKeysize=maxKeyLength;

    FILE* fptr=fopen(filename, "r");
    if (!fptr) 
    {
        perror("Error opening file");
        return -1;
    }


    char* block= malloc(maxKeyLength*3+1);
    fread(block, 1, maxKeyLength*3, fptr);

    for(int i=minKeyLength;i<=maxKeyLength;i++)
    {
        char* block1=malloc(i+1);
        char* block2=malloc(i+1);

        memcpy(block1, block, i);
        memcpy(block2, block+i, i);

        block1[i]='\0';
        block2[i]='\0';
        // printf("%s %s \n", block1, block2);

        char* bin1=base64ToBinary(block1);
        char* bin2=base64ToBinary(block2);

        int sum=computeHammingDistanceOfBinary(bin1, bin2);

        // printf("%d sum = %d\n", i, sum);

        if(sum<min)
        {
            min=sum;
            minKeysize=i;
        }


        free(bin1);
        free(bin2);
        free(block1);
        free(block2);

    }
    


    free(block);
    fclose(fptr);
    return minKeysize;
}