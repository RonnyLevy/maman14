#include "language_structure.h"

void ic_and_dc_counters_initialization()
{
	*ic = (word){100}; /* first address 100 decimal */
	
	*dc = (word){0};
}

char* convert_decimal_to_binary(int num)
{ 
	const int size_of_int = sizeof(int); 

    char binary[size_of_int]; 
   
    int i = 0; 
    
    while (num > 0)
    {  
        binary[i] = num % 2; 
        
        num = num / 2; 
        
        i++; 
    }
    
    return binary; 
}

bool is_label_exist_in_symbol_table(const char* label_name)
{
	int symbol_table_index = 0;
	
	for ( ; symbol_table_index < MAX_LINES_IN_SOURCE_CODE ; symbol_table_index++)
	{
		if (!strcmp(label_name, *(symbol_table_ptr + symbol_table_index) -> name))
		{
			return true;
		}
	}
	
	return false;
}

bool is_instruction_valid(const char* instruction)
{
	if      (!strcmp(instruction, MOV))  return true;
	 
	else if (!strcmp(instruction, CMP))  return true;
	
	else if (!strcmp(instruction, ADD))  return true;
	
	else if (!strcmp(instruction, SUB))  return true;
	
	else if (!strcmp(instruction, LEA))  return true; 
	
	else if (!strcmp(instruction, CLR))  return true;
	
	else if (!strcmp(instruction, NOT))  return true;
	
	else if (!strcmp(instruction, INC))  return true;
	
	else if (!strcmp(instruction, DEC))  return true;
	
	else if (!strcmp(instruction, JMP))  return true;
	
	else if (!strcmp(instruction, BNE))  return true;
	
	else if (!strcmp(instruction, JSR))  return true;
	
	else if (!strcmp(instruction, RED))  return true;
	
	else if (!strcmp(instruction, PRN))  return true;
	
	else if (!strcmp(instruction, RTS))  return true;
	
	else if (!strcmp(instruction, STOP)) return true;
	
	else                                 return false;
}

bool is_operand_register(const char* operand)
{
	if      (!strcmp(operand, "r0")) return true;
	 
	else if (!strcmp(operand, "r1")) return true;
	
	else if (!strcmp(operand, "r2")) return true;
	
	else if (!strcmp(operand, "r3")) return true;
	
	else if (!strcmp(operand, "r4")) return true; 
	
	else if (!strcmp(operand, "r5")) return true;
	
	else if (!strcmp(operand, "r6")) return true;
	
	else if (!strcmp(operand, "r7")) return true;
	
	else                             return false;	
}
