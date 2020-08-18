#ifndef __command_hash_table_h__

#define __command_hash_table_h__

#define COMMAND_NUM 16

#include "stdio.h"
#include "string.h"
#include "language_structure.h"

/* 
	create dictionary of <command name, <opcode, func>> 
	
	the goal: encode command name to opcode and func.
	
	example: for mov command and direct addresssing => opcode = 000000, func = 00000.
*/

struct opcode_func
{
	unsigned op_code: 6;
	
	unsigned func: 5; /* if not declared , put 0 */
}
typedef opcode_func;

struct command
{
	char* name;
	
	opcode_func opcode_func_pair;
}
typedef command;

static char MOV[] = "mov";

static char CMP[] = "cmp";

static char ADD[] = "add";

static char SUB[] = "sub";

static char LEA[] = "lea";

static char CLR[] = "clr";

static char NOT[] = "not";

static char INC[] = "inc";

static char DEC[] = "dec";

static char JMP[] = "jmp";

static char BNE[] = "bne";

static char JSR[] = "jsr";

static char RED[] = "red";

static char PRN[] = "prn";

static char RTS[] = "rts";

static char STOP[] = "stop";

static command command_table[COMMAND_NUM] = {
												MOV,  {000000, 00000},
										
											  	CMP,  {000001, 00000},
										
											  	ADD,  {000010, 00001},
										
											  	SUB,  {000010, 00010},
										
											  	LEA,  {000100, 00000},
										
											  	CLR,  {000101, 00001},
										
											  	NOT,  {000101, 00010},
										
											  	INC,  {000101, 00011},
										
											  	DEC,  {000101, 00100},
										
											  	JMP,  {001001, 00001},
										
											  	BNE,  {001001, 00010},
										
											  	JSR,  {001001, 00011},
										
	   										  	RED,  {001100, 00000},
										
										      	PRN,  {001101, 00000},
										
										      	RTS,  {001110, 00000},
										
										      	STOP, {001111, 00000} 
											};

static command* command_table_ptr = command_table;

opcode_func* get_opcode_and_func_by_name(const char* name);

#endif
