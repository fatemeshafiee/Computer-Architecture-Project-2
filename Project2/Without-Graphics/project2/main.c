#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//H:\4\architecture\project2\UIsinglecycle\tests\assembeld\program3.mc

int instruction_int [65536];
char instruction [65536][33];
int instruction_size = 0;

int UseOfMemory = 0;

void Add1(int * input)
{
    *input = *input+1;
}

void read_instruction()
{
    char path[100] = "";
    printf("\n Enter address of your file: ");
    gets(path);
    FILE* Input = fopen(path, "r");
    if (Input == NULL)
    {
        printf("NOT FOUND!");


        exit(1);
    }
    while (fgets(instruction[(instruction_size)], 200, Input))
    {
        printf("%s\n", instruction[(instruction_size)]);
        instruction[(instruction_size)][strlen(instruction[(instruction_size)]) - 1] = '\0';
        (instruction_size) = (instruction_size)+1;
        instruction_int[instruction_size-1] = convert_string_to_int(instruction[instruction_size-1]);
    }
}

char* my_strcat(char* destination, char* source)
{
    strcpy(destination + strlen(destination), source);
    return destination;
}

int Binary_to_decimal (char * binary_result)
{
    long long int result = 0;
    for (int i = 0 ; i < strlen(binary_result); i++)
    {
        int power = strlen(binary_result) -1 - i;
        if(binary_result[i]=='1')
        {

            result += pow(2,power);
        }

    }
    return result;
}

void Decimal_to_binary(int input,char * binary, int binary_size)
{
    int is_negativ=0;

    if(input<0)
    {
        input *=-1;
        is_negativ=1;
    }
    while (input!=0)
    {
        int remind = input%2;
        input = input/2;
        char * to_be_add= (char *)calloc(2, 1);
        to_be_add[0] = '0'+remind ;
        my_strcat(binary,to_be_add);

    }
    while (strlen(binary) <binary_size)
    {
        char * to_be_add= (char *)calloc(2, 1);
        to_be_add[0] = '0' ;
        my_strcat(binary,to_be_add);
    }
    if((strlen(binary)>binary_size) && binary_size==16)
    {
        printf("the offset size is grater than 16 \n");
        exit(1);
    }

    if(is_negativ)
    {
        int index = 0;
        while (binary[index]!='1')
        {
            index++;
        }
        index++;
        for (int i = index; i < strlen(binary); i++)
        {

            if(binary[i]=='0')
                binary[i]='1';
            else {
                binary[i] = '0';
            }
        }

    }
    strrev(binary);


}

int convert_string_to_int(char * input)
{
    int t = 0;
    if(input[0]!= '-')
    {
        // printf("%llu\n", strlen(input));
        for ( int  i = strlen(input)-1; i >= 0; i--)
        {
            t += (input[i] - '0')*pow(10,strlen(input)-1-i);
        }
        return t;
    }
    for ( int  i = strlen(input)-1; i > 0; i--)
    {
        t += (input[i] - '0')*pow(10,strlen(input)-1-i);
    }
    t*=-1;
    return t;
}

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

int mux(int src0, int src1, int control_signal)
{
    if(control_signal)
        return src1;
    return src0;
}

int ALU(int src1, int src2, int* conrtol_signals, int * zero, int extension_true)
{
    if(conrtol_signals[10] && extension_true )
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

int and_component(int control_signal, int zero)
{
    return (control_signal & zero);
}

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

void Write_to_Register_function(int Write_to_register_value, int write_signal, int write_register_index , int * Register )
{
    if(write_signal)
        Register[write_register_index] = Write_to_register_value;
}

void print_register(int * Register)
{
    printf("%s\n", "-----------------------------------------------");
    for (int i = 0; i < 16; i++)
    {
        printf("%d\n", Register[i]);
    }

    printf("%s\n", "-----------------------------------------------");
}

void print_finals(int pc, int * Register_counter)
{
    printf("Total Instructions: %d\n", pc);
    printf("Total Number of using Memory: %d\n", UseOfMemory);
    printf("Percentage of usage of each Register:\n");
    int sum = 0;
    for(int i = 0; i < 16; i++)
        sum += Register_counter[i];
    for(int i = 0; i < 16; i++)
        printf("%d th Register percentage of use: %d\n", i, (Register_counter[i]));
}

void single_cycle()
{
    int pc = 0;
    int zero;
    int Register_counter[16] = {0};

    int control_signals[11];
    int  Register[16] ={0};

    read_instruction();
    char ** binary_instruction;
    binary_instruction = (char **) calloc(instruction_size, sizeof(char*));

    for(int i = 0; i < instruction_size; i++)
        binary_instruction[i] = (char *) calloc(33, sizeof(char *));

    for(int i = 0; i < instruction_size ; i++)
    {
        Decimal_to_binary(instruction_int[i],binary_instruction[i],32);
        printf("%s\n", binary_instruction[i]);
    }

    while (pc < instruction_size)
    {
        if(instruction_int[pc]==234881024)
        {
            Add1(&pc);
            break;
        }
        int read_register1, read_register2, write_register_index, immediate, op_code;
        int ALU_result;

        zero = 0;

        Fetch(&read_register1, &read_register2, &write_register_index, &immediate, &op_code, binary_instruction[pc]);

        Control_Unit(control_signals, op_code);
        if((op_code > 4 )&& (op_code < 11))
            ALU_result = ALU(Register[read_register1], mux(Register[read_register2], immediate, control_signals[8]), control_signals, &zero, 1);
        else
            ALU_result = ALU(Register[read_register1], mux(Register[read_register2], immediate, control_signals[8]), control_signals, &zero, 0);
        int pcplus;

        pc = next_PC(pc, control_signals, zero, immediate, read_register2, read_register1 , &pcplus, Register);

        int ReadMemoryData = 0 ;


        memory_read_write(control_signals,ALU_result,Register[read_register2],&ReadMemoryData);
        int Write_to_register_value = mux(ALU_result,ReadMemoryData,control_signals[5]);
        Write_to_register_value =  mux(Write_to_register_value ,pcplus ,control_signals[0]);
        write_register_index = mux(read_register2, write_register_index, control_signals[1]);

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
        Write_to_Register_function(Write_to_register_value,control_signals[9],write_register_index,  Register);


        print_register(Register);

    }

    print_finals(pc , Register_counter);
}

int main()
{

    single_cycle();
    return 0;
}
