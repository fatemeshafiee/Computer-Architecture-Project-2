#ifndef WRITEINREG_H
#define WRITEINREG_H

#endif // WRITEINREG_H
#include <stdio.h>
#include "memory.h"

void Write_to_Register_function(int Write_to_register_value, int write_signal, int write_register_index , int * Register )
{
    if(write_signal)
        Register[write_register_index] = Write_to_register_value;
}
