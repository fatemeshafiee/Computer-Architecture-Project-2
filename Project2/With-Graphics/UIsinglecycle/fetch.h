#ifndef FETCH_H
#define FETCH_H
#endif // FETCH_H
//#include "definedfunctions.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "readinstruction.h"

void Fetch( int  * read_register1,int * read_register2,int * write_register,int * immediate, int * op_code, char * binary_instruction)
{
    char * read1_char= (char *)calloc(5, 1);
    char * read2_char= (char *)calloc(5, 1);
    char * write_char= (char *)calloc(5, 1);
    char * immidiate_char= (char *)calloc(17, 1);
    char * opcode_char= (char *)calloc(5, 1);
    for (int i = 8 ; i < 12; i++)
    {
        char * to_be_add = (char *)calloc(2,1);
        to_be_add[0] = binary_instruction[i];
        my_strcat(read1_char,to_be_add);
    }
    for (int i = 12 ; i < 16; i++)
    {
        char * to_be_add = (char *)calloc(2,1);
        to_be_add[0] = binary_instruction[i];
        my_strcat(read2_char,to_be_add);
    }
    for (int i = 16 ; i < 20; i++)
    {
        char * to_be_add = (char *)calloc(2,1);
        to_be_add[0] = binary_instruction[i];
        my_strcat(write_char,to_be_add);
    }
    for (int i = 16 ; i < 32; i++)
    {
        char * to_be_add = (char *)calloc(2,1);
        to_be_add[0] = binary_instruction[i];
        my_strcat(immidiate_char,to_be_add);
    }
    for (int i = 4; i < 8; i++)
    {
        char * to_be_add = (char *)calloc(2,1);
        to_be_add[0] = binary_instruction[i];
        my_strcat(opcode_char,to_be_add);
    }
    *read_register1 = Binary_to_decimal(read1_char);
    *read_register2 = Binary_to_decimal(read2_char);
    *write_register = Binary_to_decimal(write_char);
    *immediate       = Binary_to_decimal(immidiate_char);
    *op_code        = Binary_to_decimal(opcode_char);
}
