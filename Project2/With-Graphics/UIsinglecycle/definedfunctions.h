#ifndef DEFINEDFUNCTIONS_H
#define DEFINEDFUNCTIONS_H

#endif // DEFINEDFUNCTIONS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int convert_string_to_int(char * input)
{
    int t = 0;
    if(input[0]!= '-')
    {
        // printf("%llu\n", strlen(input));
        for ( int  i = strlen(input)-1; i >= 0; i--)
        {
            t += (input[i] - '0')*pow(10,strlen(input)-1-i);
        }
        return t;
    }
    for ( int  i = strlen(input)-1; i > 0; i--)
    {
        t += (input[i] - '0')*pow(10,strlen(input)-1-i);
    }
    t*=-1;
    return t;
}

char* my_strcat(char* destination, char* source)
{
    strcpy(destination + strlen(destination), source);
    return destination;
}

int Binary_to_decimal (char * binary_result)
{
    long long int result = 0;
    for (int i = 0 ; i < strlen(binary_result); i++)
    {
        int power = strlen(binary_result) -1 - i;
        if(binary_result[i]=='1')
        {

            result += pow(2,power);
        }

    }
    return result;
}

void Decimal_to_binary(int input,char * binary, int binary_size)
{
    int is_negativ=0;

    if(input<0)
    {
        input *=-1;
        is_negativ=1;
    }
    while (input!=0)
    {
        int remind = input%2;
        input = input/2;
        char * to_be_add= (char *)calloc(2, 1);
        to_be_add[0] = '0'+remind ;
        my_strcat(binary,to_be_add);

    }
    while (strlen(binary) <binary_size)
    {
        char * to_be_add= (char *)calloc(2, 1);
        to_be_add[0] = '0' ;
        my_strcat(binary,to_be_add);
    }
    if((strlen(binary)>binary_size) && binary_size==16)
    {
        printf("the offset size is grater than 16 \n");
        exit(1);
    }

    if(is_negativ)
    {
        int index = 0;
        while (binary[index]!='1')
        {
            index++;
        }
        index++;
        for (int i = index; i < strlen(binary); i++)
        {

            if(binary[i]=='0')
                binary[i]='1';
            else {
                binary[i] = '0';
            }
        }

    }
    strrev(binary);
}
