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
			
			error_in_source_code = true;
			
			return;
		}
	}
		
	int val = atoi(operand1);
					
	if (val == 0)
	{
		printf("%s in line %d\n", data_guidance_invalid_number, line_number);
				
		error_in_source_code = true;
			
		return;
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
				
				error_in_source_code = true;
			
				return false;
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
		
		error_in_source_code = true;
			
		return;
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

bool is_instruction_valid(const char* instruction, const char* operand1, const char* operand2, addressing_type* operand1_addressing_type, addressing_type* operand2_addressing_type, const int line_number)
{
	remove_trailing_spaces(instruction);

	if (!strcmp(instruction, MOV))
	{
		printf("rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n");
	
		/* check if exist two operands */
	
		if (operand1 != NULL && operand2 != NULL)
		{
			if (!is_string_empty(operand1) && !is_string_empty(operand2))
			{
				/* check the addresssing type of source and destination operands */
			
				/* source addressing : 0, 1, 3 */
			
				if (does_immediate_addressing(operand1))
				{
					*operand1_addressing_type = immediate;
				}
							
				else if (does_direct_addressing(operand1))
				{
					*operand1_addressing_type = direct;
				}
				
				else if (does_direct_register_addressing(operand1))
				{
					*operand1_addressing_type = direct_register;
				}
				
				else
				{
					printf("%s in line %d\n", mov_src_addressing_error, line_number);
					
					command_not_valid();
			
					return false;
				}
				
				/* destination addressing : 1, 3 */
				
				if (does_direct_addressing(operand2))
				{
					*operand2_addressing_type = direct;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_direct_register_addressing(operand2))
				{
					*operand2_addressing_type = direct_register;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else
				{
					printf("%s in line %d\n", mov_dst_addressing_error, line_number);
					
					command_not_valid();
					
					return false;
				}				
			}
			
			else
			{
				printf("%s in line %d\n", mov_arguments_error, line_number);
				
				command_not_valid();
				
				return false;
			}
		}
		else 
		{
			printf("%s in line %d\n", mov_arguments_error, line_number);
			
			command_not_valid();
			
			return false;
		}
	}
	 
	else if (!strcmp(instruction, CMP))
	{
		printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n");
	
		if (operand1 != NULL && operand2 != NULL)
		{
			/* check the addresssing type of source and destination operands */
			
			/* source addressing : 0, 1, 3 */
			
			if (does_immediate_addressing(operand1))
			{
				*operand1_addressing_type = immediate;
			}
							
			else if (does_direct_addressing(operand1))
			{
				*operand1_addressing_type = direct;
			}
				
			else if (does_direct_register_addressing(operand1))
			{
				*operand1_addressing_type = direct_register;
			}
				
			else
			{
				printf("%s in line %d\n", cmp_src_addressing_error, line_number);
					
				command_not_valid();
			
				return false;
			}
				
			/* destination addressing : 0, 1, 3 */
				
			if (does_immediate_addressing(operand2))
			{
				*operand2_addressing_type = immediate;
				
				error_in_source_code = false;
					
				return true;
			}
							
			else if (does_direct_addressing(operand2))
			{
				*operand2_addressing_type = direct;
				
				error_in_source_code = false;
					
				return true;
			}
				
			else if (does_direct_register_addressing(operand2))
			{
				*operand2_addressing_type = direct_register;
				
				error_in_source_code = false;
					
				return true;	
			}
				
			else
			{
				printf("%s in line %d\n", cmp_arguments_error, line_number);
					
				command_not_valid();
			
				return false;
			}
		}
		else 
		{
			printf("%s in line %d\n", cmp_arguments_error, line_number);
					
			command_not_valid();
			
			return false;
		}
	}
	
	else if (!strcmp(instruction, ADD))
	{
		printf("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n");
	
		if (operand1 != NULL && operand2 != NULL)
		{
			if (!is_string_empty(operand1) && !is_string_empty(operand2))
			{
				/* check the addresssing type of source and destination operands */
			
				/* source addressing : 0, 1, 3 :*/
				
				if (does_immediate_addressing(operand1))
				{
					*operand1_addressing_type = immediate;
				}
							
				else if (does_direct_addressing(operand1))
				{
					*operand1_addressing_type = direct;
				}
				
				else if (does_direct_register_addressing(operand1))
				{
					*operand1_addressing_type = direct_register;
				}
				
				else
				{
					printf("%s in line %d\n", add_src_addressing_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
				
				/* destination addressing: 1, 3 */
				
				if (does_direct_addressing(operand2))
				{
					*operand2_addressing_type = direct;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_direct_register_addressing(operand2))
				{
					*operand2_addressing_type = direct_register;
					
					error_in_source_code = false;
					
					return true;	
				}
				
				else
				{
					printf("%s in line %d\n", add_dst_addressing_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
			}
			
			else
			{
				printf("%s in line %d\n", add_arguments_error, line_number);
					
				command_not_valid();
			
				return false;
			}
		}
		
		else
		{
			printf("%s in line %d\n", add_arguments_error, line_number);
					
			command_not_valid();
			
			return false;
		}
	}
	
	else if (!strcmp(instruction, SUB))
	{
		printf("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\n");
	
		if (operand1 != NULL && operand2 != NULL)
		{
			if (!is_string_empty(operand1) && !is_string_empty(operand2))
			{
				/* check the addresssing type of source and destination operands */
			
				/* source addressing : 0, 1, 3 */
				
				if (does_immediate_addressing(operand1))
				{
					*operand1_addressing_type = immediate;
				}
							
				else if (does_direct_addressing(operand1))
				{
					*operand1_addressing_type = direct;
				}
				
				else if (does_direct_register_addressing(operand1))
				{
					*operand1_addressing_type = direct_register;
				}
				
				else
				{
					printf("%s in line %d\n", sub_src_addressing_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
				
				/* destination addressing: 1, 3 */
				
				if (does_direct_addressing(operand2))
				{
					*operand2_addressing_type = direct;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_direct_register_addressing(operand2))
				{
					*operand2_addressing_type = direct_register;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else
				{
					printf("%s in line %d\n", sub_dst_addressing_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
			}
			
			else
			{
				printf("%s in line %d\n", sub_arguments_error, line_number);	
					
				command_not_valid();
			
				return false;
			}
			
		}
		
		else
		{
			printf("%s in line %d\n", sub_arguments_error, line_number);	
					
			command_not_valid();
			
			return false;
		}
	}
	
	else if (!strcmp(instruction, LEA))
	{
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
		
		if (operand1 != NULL && operand2 != NULL)
		{
			if (!is_string_empty(operand1) && !is_string_empty(operand2))
			{
				/* check the addresssing type of source and destination operands */
			
				/* source addressing : 1 */
				
				if (does_direct_addressing(operand1))
				{
					*operand1_addressing_type = immediate;
				}
				
				else
				{
					printf("%s in line %d\n", lea_src_addressing_error, line_number);
					
					command_not_valid();
			
					return false;
				}
				
				/* destination addressing: 1, 3 */
				
				if (does_direct_addressing(operand2))
				{
					*operand2_addressing_type = direct;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_direct_register_addressing(operand2))
				{
					*operand2_addressing_type = direct_register;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else
				{
					printf("%s in line %d\n", lea_src_addressing_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
			}
			
			else
			{
				printf("%s in line %d\n", lea_arguments_error, line_number);
					
				command_not_valid();
			
				return false;
			}
		}
		
		else
		{
			printf("%s in line %d\n", lea_arguments_error, line_number);
					
			command_not_valid();
			
			return false;
		}
	} 
	
	else if (!strcmp(instruction, CLR))
	{
		printf("---------------------------------------------------\n");
	
		/* The command write like this: clr r2. r2 is destination (operand2).
		
		   Because our definition of token assume destination after comma, we will refer to operand1 as a destination and
		   
		   operand2 not exist. 
		*/
		
		if ((operand1 != NULL && !is_string_empty(operand1)) && (operand2 == NULL || is_string_empty(operand2)))
		{
			if (is_string_int_num(operand1) || strchr(operand1, ' ') != NULL)
			{
				printf("%s in line %d\n", clr_dst_addressing_error, line_number);
					
				command_not_valid();
			
				return false;
			}
			
			else
			{
				/* recognize addressing type */
				
				/* destination addressing: 1, 3 */
				
				if (does_direct_addressing(operand1))
				{
					*operand2_addressing_type = direct;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_direct_register_addressing(operand1))
				{
					*operand2_addressing_type = direct_register;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else
				{
					printf("%s in line %d\n", clr_argument_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
			}	
		}
		
		else
		{
			printf("%s in line %d\n", clr_argument_error, line_number);
					
			command_not_valid();
			
			return false;
		}
	}
	
	else if (!strcmp(instruction, NOT))
	{
		printf("))))))))))))))))))))))))))))))))))))))))))\n");
	
		/* The command write like this: not r2. r2 is destination (operand2).
		
		   Because our definition of token assume destination after comma, we will refer to operand1 as a destination and
		   
		   operand2 not exist. 
		*/
		
		if ((operand1 != NULL && !is_string_empty(operand1)) && (operand2 == NULL || is_string_empty(operand2)))
		{
			if (is_string_int_num(operand1) || strchr(operand1, ' ') != NULL)
			{
				printf("%s in line %d\n", not_dst_addressing_error, line_number);
					
				command_not_valid();
			
				return false;
			}
			
			else
			{
				/* recognize addressing type */
				
				/* destination addressing: 1, 3 */
				
				if (does_direct_addressing(operand1))
				{
					*operand2_addressing_type = direct;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_direct_register_addressing(operand1))
				{
					*operand2_addressing_type = direct_register;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else
				{
					printf("%s in line %d\n", not_argument_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
			}	
		}
		
		else
		{
			printf("%s in line %d\n", not_argument_error, line_number);
					
			command_not_valid();
			
			return false;
		}	
	}
	
	else if (!strcmp(instruction, INC))
	{
		printf("(((((((((((((((((((((((((((((((((((((((((((((((\n");
	
		/* The command write like this: inc r2. r2 is destination (operand2).
		
		   Because our definition of token assume destination after comma, we will refer to operand1 as a destination and
		   
		   operand2 not exist. 
		*/
		
		if ((operand1 != NULL && !is_string_empty(operand1)) && (operand2 == NULL || is_string_empty(operand2)))
		{
			if (is_string_int_num(operand1) || strchr(operand1, ' ') != NULL)
			{
				printf("%s in line %d\n", inc_dst_addressing_error, line_number);
					
				command_not_valid();
			
				return false;
			}
			
			else
			{
				/* recognize addressing type */
				
				/* destination addressing: 1, 3 */
				
				if (does_direct_addressing(operand1))
				{
					*operand2_addressing_type = direct;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_direct_register_addressing(operand1))
				{
					*operand2_addressing_type = direct_register;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else
				{
					printf("%s in line %d\n", inc_argument_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
			}	
		}
		
		else
		{
			printf("%s in line %d\n", inc_argument_error, line_number);
					
			command_not_valid();
			
			return false;
		}
	}
	
	else if (!strcmp(instruction, DEC))
	{
		printf("*************************************8\n");
	
		/* The command write like this: dec r4. r4 is destination (operand2).
		
		   Because our definition of token assume destination after comma, we will refer to operand1 as a destination and
		   
		   operand2 not exist. 
		*/
		
		if ((operand1 != NULL && !is_string_empty(operand1)) && (operand2 == NULL || is_string_empty(operand2)))
		{
			if (is_string_int_num(operand1) || strchr(operand1, ' ') != NULL)
			{
				printf("%s in line %d\n", dec_dst_addressing_error, line_number);
					
				command_not_valid();
			
				return false;
			}
			
			else
			{
				/* recognize addressing type */
				
				/* destination addressing: 1, 3 */
				
				if (does_direct_addressing(operand1))
				{
					*operand2_addressing_type = direct;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_direct_register_addressing(operand1))
				{
					*operand2_addressing_type = direct_register;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else
				{
					printf("%s in line %d\n", dec_argument_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
			}	
		}
		
		else
		{
			printf("%s in line %d\n", dec_argument_error, line_number);
					
			command_not_valid();
			
			return false;
		}
	}
	
	else if (!strcmp(instruction, JMP))
	{
		printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&7\n");
	
		/* The command write like this: jmp &Line. &Line is destination (operand2).
		
		   Because our definition of token assume destination after comma, we will refer to operand1 as a destination and
		   
		   operand2 not exist. 
		*/
		
		if ((operand1 != NULL && !is_string_empty(operand1)) && (operand2 == NULL || is_string_empty(operand2)))
		{
			if (is_string_int_num(operand1) || strchr(operand1, ' ') != NULL)
			{
				printf("%s in line %d\n", jmp_dst_addressing_error, line_number);
					
				command_not_valid();
			
				return false;
			}
			
			else
			{
				/* recognize addressing type */
				
				/* destination addressing: 1, 3 */
				
				if (does_direct_addressing(operand1))
				{
					*operand2_addressing_type = direct;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_relative_addressing(operand1))
				{
					*operand2_addressing_type = relative;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else
				{
					printf("%s in line %d\n", jmp_argument_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
			}	
		}
		
		else
		{
			printf("%s in line %d\n", jmp_argument_error, line_number);
					
			command_not_valid();
			
			return false;
		}
	}
	
	else if (!strcmp(instruction, BNE))
	{
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^6\n");
		
		/* The command write like this: bne Line. Line is destination (operand2).
		
		   Because our definition of token assume destination after comma, we will refer to operand1 as a destination and
		   
		   operand2 not exist. 
		*/
		
		if ((operand1 != NULL && !is_string_empty(operand1)) && (operand2 == NULL || is_string_empty(operand2)))
		{
			if (is_string_int_num(operand1) || strchr(operand1, ' ') != NULL)
			{
				printf("%s in line %d\n", bne_dst_addressing_error, line_number);
					
				command_not_valid();
			
				return false;
			}
			
			else
			{
				/* recognize addressing type */
				
				/* destination addressing: 1, 3 */
				
				if (does_direct_addressing(operand1))
				{
					*operand2_addressing_type = direct;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_relative_addressing(operand1))
				{
					*operand2_addressing_type = relative;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else
				{
					printf("%s in line %d\n", bne_argument_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
			}	
		}
		
		else
		{
			printf("%s in line %d\n", bne_argument_error, line_number);
					
			command_not_valid();
			
			return false;
		}
	}
	
	else if (!strcmp(instruction, JSR))
	{
		printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%55\n");
	
		/* The command write like this: jst SUBR. SUBR is destination (operand2).
		
		   Because our definition of token assume destination after comma, we will refer to operand1 as a destination and
		   
		   operand2 not exist. 
		*/
		
		if ((operand1 != NULL && !is_string_empty(operand1)) && (operand2 == NULL || is_string_empty(operand2)))
		{
			if (is_string_int_num(operand1) || strchr(operand1, ' ') != NULL)
			{
				printf("%s in line %d\n", jsr_dst_addressing_error, line_number);
					
				command_not_valid();
			
				return false;
			}
			
			else
			{
				/* recognize addressing type */
				
				/* destination addressing: 1, 3 */
				
				if (does_direct_addressing(operand1))
				{
					*operand2_addressing_type = direct;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_relative_addressing(operand1))
				{
					*operand2_addressing_type = relative;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else
				{
					printf("%s in line %d\n", jsr_argument_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
			}	
		}
		
		else
		{
			printf("%s in line %d\n", jsr_argument_error, line_number);
					
			command_not_valid();
			
			return false;
		}
	}
	
	else if (!strcmp(instruction, RED))
	{
		printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$44\n");
	
		/* The command write like this: red r1. r1 is destination (operand2).
		
		   Because our definition of token assume destination after comma, we will refer to operand1 as a destination and
		   
		   operand2 not exist. 
		*/
		
		if ((operand1 != NULL && !is_string_empty(operand1)) && (operand2 == NULL || is_string_empty(operand2)))
		{
			if (is_string_int_num(operand1) || strchr(operand1, ' ') != NULL)
			{
				printf("%s in line %d\n", red_dst_addressing_error, line_number);
					
				command_not_valid();
			
				return false;
			}
			
			else
			{
				/* recognize addressing type */
				
				/* destination addressing: 1, 3 */
				
				if (does_direct_addressing(operand1))
				{
					*operand2_addressing_type = direct;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_direct_register_addressing(operand1))
				{
					*operand2_addressing_type = direct_register;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else
				{
					printf("%s in line %d\n", red_argument_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
			}	
		}
		
		else
		{
			printf("%s in line %d\n", red_argument_error, line_number);
					
			command_not_valid();
			
			return false;
		}
	}
	
	else if (!strcmp(instruction, PRN))
	{
		/* The command write like this: prn r1. r1 is destination (operand2).
		
		   Because our definition of token assume destination after comma, we will refer to operand1 as a destination and
		   
		   operand2 not exist. 
		*/
		
		if ((operand1 != NULL && !is_string_empty(operand1)) && (operand2 == NULL || is_string_empty(operand2)))
		{
			if (is_string_int_num(operand1) || strchr(operand1, ' ') != NULL)
			{
				printf("%s in line %d\n", prn_dst_addressing_error, line_number);
					
				command_not_valid();
			
				return false;
			}
			
			else
			{
				/* recognize addressing type */
				
				/* destination addressing: 0, 1, 3 */
					
				if (does_immediate_addressing(operand1))
				{
					*operand2_addressing_type = immediate;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_direct_addressing(operand1))
				{
					*operand2_addressing_type = direct;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else if (does_relative_addressing(operand1))
				{
					*operand2_addressing_type = relative;
					
					error_in_source_code = false;
					
					return true;
				}
				
				else
				{
					printf("%s in line %d\n", prn_argument_error, line_number);
					
					command_not_valid();
			
					return false;
				}	
			}	
		}
		
		else
		{
			printf("%s in line %d\n", prn_argument_error, line_number);
					
			command_not_valid();
			
			return false;
		}
	}
	
	else if (!strcmp(instruction, RTS))
	{
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2\n");
	
		/* completely without operands */
		
		if (operand1 != NULL || !is_string_empty(operand1) || operand2 != NULL || !is_string_empty(operand2))
		{
			printf("%s in line %d\n", rts_argument_error, line_number);
					
			command_not_valid();
			
			return false;
		}
		else
		{
			error_in_source_code = false;
					
			return true;
		} 
	}
	
	else if (!strcmp(instruction, STOP))
	{
		/* completely without operands */
		
		if ((operand1 == NULL || is_string_empty(operand1)) && (operand2 == NULL || is_string_empty(operand2)))
		{
			error_in_source_code = false;
					
			return true;
		}
		else
		{
			printf("%s in line %d\n", stop_argument_error, line_number);
					
			command_not_valid();
			
			return false;
		} 
	}
	
	else 
	{
		printf("%s in line %d\n", no_legal_command, line_number);
					
		command_not_valid();
			
		return false;
	}
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
			printf("%s in line %d\n", immediate_addressing_error, line_number);
						
			error_in_source_code = true;
			
			return false;				
		}
		
	    return true;
	}
	
	return false;	
}

bool does_direct_addressing(const char* operand)
{
	/* This addressing types, will be reflected in the appearance of a label.
	
	   It is possible that the label at this time, is not yet in the label table, because it will only be defined in a few more 		
	   lines.
	   
	   At first running, it is still not possible to know if this is really a label.

	   Therefore, suppose yes (if of course the string itself is legal), and only in the second passage we can get 
	   	
	   more details about it.
	   
	   label must start in char (no number or _) and cannot equal to keyword in our lang.
	
	*/	
	
	char first_char = operand[0];
	
	if (isdigit(first_char) || strchr(operand, ' ') != NULL)
	{
		printf("%d in line %d\n", immediate_addressing_error, line_number);
		
		error_in_source_code = true;
			
		return false;
	}
	
	return true;	
}

bool does_relative_addressing(const char* operand)
{
	char first_char = operand[0];

	if (first_char == relative_addresssing)
	{
		if (isdigit(operand[1]) || strchr(operand, ' ') != NULL)
		{
			printf("%d in line %d\n", immediate_addressing_error, line_number);
		
			error_in_source_code = true;
			
			return false;
		}
		
		return true;		
	}
	
	return false;	
}

bool does_direct_register_addressing(const char* operand)
{
	return is_operand_register(operand);
}

void command_not_valid()
{
	*operand1_addressing_type = *operand2_addressing_type = illegal;
					
	error_in_source_code = true;
}

