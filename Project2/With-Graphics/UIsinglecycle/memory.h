#ifndef MEMORY_H
#define MEMORY_H

#endif // MEMORY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nextpc.h"

extern int instruction_int [65536];

void memory_read_write(int * control_signals, int ALU_result, int WriteData, int * ReadDate)
{
    if(control_signals[4])
    {
        *ReadDate = instruction_int[ALU_result];
        return;
    }
    if(control_signals[7])
    {
        instruction_int[ALU_result] = WriteData;
        return;
    }
}
