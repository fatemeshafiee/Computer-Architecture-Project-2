#ifndef ALU_H
#define ALU_H

#endif // ALU_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "extention.h"
#include "controlunit.h"

int ALU(int src1, int src2, int* conrtol_signals, int * zero, int extension_true)
{
    if(conrtol_signals[10] && extension_true)
        extension(&src2, conrtol_signals[10]);
    switch (conrtol_signals[6])
    {
    case 0:
        return src1+src2;
    case 1:
        //I have delted the "not" part for zero, is that okay?
        (*zero) = (src1 == src2);
        return src1 - src2;
    case 2:
        return src1 < src2;
    case 3:
        return src1 | src2;
    case 4:
        return ~(src1 & src2);
    case 5:
        return (src2 << 16);
    }
}
