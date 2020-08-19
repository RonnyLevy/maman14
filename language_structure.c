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
	if (label_name == NULL) return false;

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

void parse_data_guidance_operands(const char* operand1, const char* operand2)
{
	if (operand1 == NULL && operand2 == NULL)
	{
		printf("%s in line %d\n", data_guidance_no_operand, line_number);
			
		exit(-1);
	}
		
	if (operand1 == NULL && operand2 != NULL)
	{
		printf("%s in line %d\n", data_guidance_no_first_argument, line_number);
			
		exit(-1);
	}
		
	int val = atoi(operand1);
			
	if (val == 0)
	{
		printf("%s in line %d\n", data_guidance_invalid_number, line_number);
				
		exit(-1);
	}
			
	word tmp = (word){val};
			
	*(dc + dc_index) = tmp;
			
	dc_index++;
		
	if (operand2 != NULL)
	{
		int val = atoi(operand2);
			
		if (val == 0)
		{
			printf("%s in line %d\n", data_guidance_invalid_number, line_number);
				
			exit(-1);
		}
			
		word num = (word){val};
			
		*(dc + dc_index) = num;
			
		dc_index++;	
	}
}

void parse_string_guidance_operands(const char* operand1, const char* operand2)
{
	if (operand1 == NULL || operand2 != NULL)
	{
		printf("%s\n", string_guidance_operand);
		
		exit(-1);
	}
	
	int string_len = strlen(operand1);
	
	int idx = 0;
	
	for ( ; idx < string_len ; idx++)
	{
		word _char = (word){operand1[idx]};
		
		*(dc + dc_index) = _char;
		
		dc_index++;
	}
	
	word end_string = (word){'\0'};
	
	*(dc + dc_index) = end_string;
	
	dc_index++; /* plus '\0' */
}

bool is_instruction_valid(const char* instruction, const char* operand1, const char* operand2)
{
	if (!strcmp(instruction, MOV))
	{
		/* check if exist two operands */
	
		if (operand1 != NULL && operand2 != NULL)
		{
			/* check the addresssing type of source and destination operands */
			
			/* for source: 0, 1, 3 :*/
			
			char first_char = operand1[0];
			
			if (first_char == immediate_addressing)
			{
				
			}
		}
		else 
		{
			return false;
		}
	}
	 
	else if (!strcmp(instruction, CMP))
	{
		
	}
	
	/* TODO */
	
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
