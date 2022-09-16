#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#endif // CONTROLUNIT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "fetch.h"

void Control_Unit(int * control_signals , int opcode)
{
    for (int i = 0; i < 11; i++)
    {
        control_signals[i] = 0;
    }
    if(opcode<5)
    { //R_type
        control_signals[1] = 1;
        control_signals[9] = 1;
        switch (opcode)
        {
        case 0:
            control_signals[6] = 0;
            break;
        case 1:
            control_signals[6] = 1;
            break;
        case 2:
            control_signals[6] = 2;
            break;
        case 3:
            control_signals[6] = 3;
            break;
        default:
            control_signals[6] = 4;
            break;

        }
    }

    else if (opcode>=5 && opcode<=12 )
    {
        switch (opcode)
        {
        case 5:
            control_signals[8] = 1;
            control_signals[9]= 1;
            control_signals [10] = 1;
            break;
        case 6:
            control_signals[6] = 2;
            control_signals[8] = 1;
            control_signals[9]= 1;
            control_signals [10] = 1;
            break;
        case 7:
            control_signals[6] = 3;
            control_signals[8] = 1;
            control_signals[9]= 1;
            break;
        case 8:
            control_signals[6] = 5;
            control_signals[8] = 1;
            control_signals[9]= 1;
            break;
        case 9:
            control_signals[4]=1;
            control_signals[5]=1;
            control_signals[8] = 1;
            control_signals[9]= 1;
            control_signals [10] = 1;
            break;
        case 10:
            control_signals[7] = 1;
            control_signals[8] = 1;
            control_signals[10] = 1;
            break;
        case 11:
            control_signals[3]=1;
            control_signals[6] = 1;
            control_signals[10] = 1;
            break;
        case 12:
            control_signals[0] = 1;
            control_signals [9] =1;
            break;

        }
    }
    else {
        // J-type
        if(opcode == 13)
            control_signals[2] = 1;
    }
}
