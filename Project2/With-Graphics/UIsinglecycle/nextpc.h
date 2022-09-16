#ifndef NEXTPC_H
#define NEXTPC_H

#endif // NEXTPC_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "littlecomponents.h"
#include "extention.h"
#include "alu.h"

int next_PC(int pc, int* control_signals, int zero, int immediate, int src1, int src2 , int * pcplus , int * Register)
{
    Add1(&pc);
    *pcplus = pc;
    //    int imm = immediate_sign;

    int immediate_sign = immediate, immediate_unsign = immediate;
    extension(&immediate_sign, 1);
    extension(&immediate_unsign, 0);
    if(control_signals[6] == 0)
        immediate_sign = ALU(pc, immediate_sign, control_signals, &zero, 0);
    else
        ALU(Register[src2], Register[src1], control_signals, &zero, 0);

    if(mux(pc, immediate_sign + pc, and_component(control_signals[3], zero)) == immediate_sign + pc)
        pc += immediate_sign;
    if(mux(pc, immediate_unsign, control_signals[2]) == immediate_unsign  && control_signals[2])
        pc = immediate_unsign;
    if(mux(pc, Register[src2], control_signals[0]) == Register[src2])
        pc = Register[src2];
    return pc;
}
