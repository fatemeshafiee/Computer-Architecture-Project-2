#ifndef READINSTRUCTION_H
#define READINSTRUCTION_H
#endif // READINSTRUCTION_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char instruction [65536][33];
int instruction_size = 0;
int instruction_int [65536];

void read_instruction(char path[])
{

    //    char path[100] = "";
    //    printf("\n Enter address of your file: ");
    //    gets(path);
    FILE* Input = fopen(path, "r");
    if (Input == NULL)
    {
        printf("NOT FOUND!");
        exit(1);
    }
    while (fgets(instruction[(instruction_size)], 200, Input))
    {
        //        printf("%s\n", instruction[(instruction_size)]);
        instruction[(instruction_size)][strlen(instruction[(instruction_size)]) - 1] = '\0';
        (instruction_size) = (instruction_size)+1;
        instruction_int[instruction_size-1] = convert_string_to_int(instruction[instruction_size-1]);
    }
}
