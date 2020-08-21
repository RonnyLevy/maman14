#include "language_structure.h"

void ic_and_dc_counters_initialization()
{
	*ic = (word){100}; /* first address 100 decimal */
	
	*dc = (word){0};
}

bool is_label_exist_in_symbol_table(const char* label_name)
{
	if (label_name == NULL) return false;

	int symbol_table_index = 0;
	
	for ( ; symbol_table_index < MAX_LINES_IN_SOURCE_CODE ; symbol_table_index++)
	{
		char* tmp_lbl = (symbol_table_ptr + symbol_table_index) -> name;
		
		if (tmp_lbl != NULL)
		{
			if (!strcmp(label_name, tmp_lbl))
			{
				return true;
			}	
		}	
	}
	
	return false;
}

void parse_data_guidance_operands(const char* operand1, const char* operand2, const int line_number)
{
	if (operand1 == NULL)
	{
		if (is_string_empty(operand1))
		{
			printf("%s in line %d\n", data_guidance_no_first_argument, line_number);
			
			exit(-1);
		}
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
		if (!is_string_empty(operand2))
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
}

void parse_string_guidance_operands(const char* operand1, const char* operand2)
{
	if (!(operand1 != NULL && operand2 == NULL))
	{
		printf("%s\n", string_guidance_operand);
		
		exit(-1);
	}
	
	int string_len = strlen(operand1);
	
	if (string_len <= 0) return;
	
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

bool is_instruction_valid(const char* instruction, const char* operand1, const char* operand2, const int line_number)
{
	if (!strcmp(instruction, MOV))
	{
		/* check if exist two operands */
	
		if (operand1 != NULL && operand2 != NULL)
		{
			if (!is_string_empty(operand1) && !is_string_empty(operand2))
			{
				/* check the addresssing type of source and destination operands */
			
				/* for source: 0, 1, 3 :*/
			
				if (does_immediate_addressing(operand1))    { return true; }
							
				else if (!does_direct_addressing(operand1)) { /* */ }
				
				else if (is_operand_register(operand1))     { return true; }
				
				else
				{
					printf("%s in line %d\n", mov_src_addressing_error, line_number);
					
					exit(-1);
				}
				
				/* for destination : */
				
				
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

bool does_immediate_addressing(const char* operand)
{
	char first_char = operand[0];

	if (first_char == immediate_addressing) /* does immediate addressing (0)? */
	{
		/* check if appear int num after # */
					
		char* sub_operand = get_substring_after_first_char(operand);
					
		bool is_digit = is_string_int_num(sub_operand);
					
		if (!is_digit)
		{
			printf("%s in line %d\n", mov_immediate_error, line_number);
						
			exit(-1);				
		}
		
		else return true;
	}
	else return false;	
}

bool does_direct_addressing(const char* operand)
{
	
}
