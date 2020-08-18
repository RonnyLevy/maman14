/* All keywords in out assembly language*/

#ifndef __language_structure_h__

#define __language_structure_h__

#include "command_hash_table.h"

#define CODE_DATA_ARR_SIZE 100

#define MAX_LINES_IN_SOURCE_CODE 100

static const char comment = ';';

static const char immediate_addressing = '#';

static const char relative_addresssing = '&';

static const char data_guidance[] = ".data";

static const char string_guidance[] = ".string";

static const char entry_guidance[] = ".entry";

static const char extern_guidance[] = ".extern";

static int* pc; /* program counter to next instruction. all addresses are 32 bit (assume 4 bytes for int) */

typedef enum { false, true } bool;

typedef enum { r0, r1, r2, r3, r4, r5, r6, r7 } _register;

typedef enum {immediate, direct, relative, direct_register} addressing_type;

/* program status word */

struct psw
{
	bool z_flag; /* zero flag */	
}
typedef psw;

struct word
{
	unsigned w: 24;
}
typedef word;

struct label
{
	char* name;

	word address; /* in decimanl */
	
	char* type; /* data / code  / external / entry */
}
typedef label;

static int symbol_table_index = 0;

static bool has_symbol = false;

static word code_img[CODE_DATA_ARR_SIZE];

static word* ic = code_img; /* instructin counter (use to determine labels addresses) */

static word data_img[CODE_DATA_ARR_SIZE];

static word* dc = data_img; /* data counter */

static int dc_index = 0;

void ic_and_dc_counters_initialization();

struct full_machine_code_command
{
	/* |op-code||source addressing||source register|||destination addressing||destination register||fucnt||A||R||E| */

	unsigned op_code: 6; /* 23 - 18 */
	
	unsigned source_addressing: 2; /* 17 - 16 */
	
	unsigned source_register: 3; /* 15 - 13 */
	
	unsigned destination_addressing: 2; /* 12 - 11 */
	
	unsigned destination_register: 3; /* 10 - 8 */
	
	unsigned func: 5; /* 7 - 3 */
	
	unsigned A: 1; /* 2 */
	
	unsigned R: 1; /* 1 */
	
	unsigned E: 1; /* 0 */ 
}
typedef full_machine_code_command;

static label symbol_table[MAX_LINES_IN_SOURCE_CODE];	

static label* symbol_table_ptr = symbol_table;

static int symbol_table_idx = 0;

bool is_label_exist_in_symbol_table(const char* label_name);

bool is_instruction_valid(const char* instruction);

char* convert_decimal_to_binary(int num);

bool is_operand_register(const char* operand); /* check if operand he's one of the eight registers */

void build_word_machine_code(); /* |op-code||source addressing||source register|||destination addressing||destination register||fucnt||A||R||E|

									op-code: 23 - 18
									
									source addressing: 17 - 16

									source register: 15 - 13
									
									destination addressing: 12 - 11
									
									destination register: 10 - 8
									
									funct: 7 - 3
									
									A: 2
									
									R: 1
									
									E: 0

								*/ 

#endif
