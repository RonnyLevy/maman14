#include "command_hash_table.h"

opcode_func* get_opcode_and_func_by_name(const char* name)
{
	int command_table_index = 0;
	
	for ( ; command_table_index < COMMAND_NUM ; command_table_index++)
	{
		if (!strcmp(name, *((command_table_ptr + command_table_index) -> name)))
		{
			/* found the command in command table - get opcode and func */
			
			return &((command_table_ptr + command_table_index) -> opcode_func_pair);
		}
	}
	
	/* This command is not some of the commands that are recognized in our language.
	
	   So, return arbitrary pair. (pair are bits and {000000}, {00000} are already taken ...)
	*/
	
	opcode_func opf = {111111, 11111};
	
	return &opf;
}
