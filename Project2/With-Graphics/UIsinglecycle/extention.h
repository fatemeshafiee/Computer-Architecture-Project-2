#ifndef EXTENTION_H
#define EXTENTION_H

#endif // EXTENTION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definedfunctions.h"

void extension(int* immidate, int control_signal)
{
    if(control_signal)
    {
        char * temp = (char *)calloc(17, 1);
        Decimal_to_binary((*immidate), temp, 16);
        if(temp[0] == '1')
        {
            int a = 1;
            for(int i = 0; i < 15; i++)
                a |= (a << 1);
            a <<= 16;
            (*immidate) |= a;
        }
        else
        {
            int a = 0;
            (*immidate) |= a;
        }
    }
    else
    {
        int a = 0;
        (*immidate) |= a;
    }
}
