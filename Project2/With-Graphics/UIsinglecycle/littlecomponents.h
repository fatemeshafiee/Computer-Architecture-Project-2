#ifndef LITTLECOMPONENTS_H
#define LITTLECOMPONENTS_H

#endif // LITTLECOMPONENTS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Add1(int * input)
{
    *input = *input+1;
}

int mux(int src0, int src1, int control_signal)
{
    if(control_signal == 1)
        return src1;
    return src0;
}

int and_component(int control_signal, int zero)
{
    return (control_signal & zero);
}
