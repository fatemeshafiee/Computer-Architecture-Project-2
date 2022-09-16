#ifndef SINGLECYCLE_H
#define SINGLECYCLE_H

#endif // SINGLECYCLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "writeinreg.h"
//C:\Users\KPS\Documents\project2\first_assembeld.txt

extern int instruction_int [65536];
extern char instruction [65536][33];
extern int instruction_size;
extern int Register[16];
extern int UseOfMemory;
extern float Register_counter[16];

char ** binary_instruction;
void single_cycle()
{   
    binary_instruction = (char **) calloc(instruction_size, sizeof(char*));

    for(int i = 0; i < instruction_size; i++)
        binary_instruction[i] = (char *) calloc(33, sizeof(char *));

    for(int i = 0; i < instruction_size ; i++)
    {
        Decimal_to_binary(instruction_int[i],binary_instruction[i],32);
    }
}

void each_cycle(int *pc, int *control_signals)
{
    int read_register1, read_register2, write_register_index, immediate, op_code;
    int ALU_result;
    int zero = 0;

    Fetch(&read_register1, &read_register2, &write_register_index, &immediate, &op_code, binary_instruction[*pc]);
    Control_Unit(control_signals, op_code);
    if((op_code > 4) && (op_code < 11))
        ALU_result = ALU(Register[read_register1], mux(Register[read_register2], immediate, control_signals[8]), control_signals, &zero, 1);
    else
        ALU_result = ALU(Register[read_register1], mux(Register[read_register2], immediate, control_signals[8]), control_signals, &zero, 0);
    int pcplus;
    *pc = next_PC(*pc, control_signals, zero, immediate, read_register2, read_register1 , &pcplus, Register);
    int ReadMemoryData = 0 ;
    memory_read_write(control_signals,ALU_result,Register[read_register2],&ReadMemoryData);
    int Write_to_register_value = mux(ALU_result,ReadMemoryData,control_signals[5]);
    Write_to_register_value =  mux(Write_to_register_value ,pcplus ,control_signals[0]);
    write_register_index = mux(read_register2, write_register_index, control_signals[1]);

    // %

    if(op_code <= 4)
    {
        Register_counter[read_register1]++;
        Register_counter[read_register2]++;
        Register_counter[write_register_index]++;
    }
    else if(op_code <= 7 ||(op_code >= 9 && op_code <= 12))
    {
        Register_counter[read_register1]++;
        Register_counter[write_register_index]++;
    }
    else if(op_code == 8)
        Register_counter[write_register_index]++;

    if(op_code >= 9 && op_code <= 10)
        UseOfMemory++;

    // %
    Write_to_Register_function(Write_to_register_value,control_signals[9],write_register_index,  Register);
    //    print_register(Register);

}
