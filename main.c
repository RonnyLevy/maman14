/* build an executable customized assembler - maman14 */

#include "file_utils.h"
#include "language_structure.h"
#include "command_hash_table.h"
#include "assembly_errors.h"

int main(int argc, char* argv[])
{
	/* Usage:
	
	   For running this elf in this dir, write in terminal: ./main arg1 arg2 ...
	
	   The arguments must contain at least one asm source code file.
	
	   For example: ./main file1.asm file2.asm file3.asm => argc = 4

	*/

	int file; /* counter loop for moving all input files (ISO C90 syntax) */

	if (argc < 2)
	{
		printf("ERROR:: please enter asm files\n");
		
		return -1;
	}

	if (!extension_validation(argv, argc))
	{
		printf("ERROR:: the input files without asm extension\n");
		
		return -2;
	}
	
	ic_and_dc_counters_initialization();
	
	for (file = 1 ; file < argc ; file++)
	{
		read_file_line_by_line(*(argv + file));
	}
	
	return 0;
}
