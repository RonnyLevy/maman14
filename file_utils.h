
/* Check files validation as format: asm */

#ifndef __file_utils_h__

#define __file_utils_h__

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include "language_structure.h"

#define MAX_LINE_SIZE 80

#define MAX_TOKENS_IN_LINE 4 /* label, command, operand1, operand2 */

static const char ASM[] = "asm";

static const char OB[]  = "ob";

static const char EXT[] = "ext";

static const char ENT[] = "ent";

char line_buffer[MAX_LINE_SIZE];

char src_line[MAX_LINE_SIZE];

const char* get_file_extension(char* file);

bool extension_validation(char* arguments[], const int num); /* reference to files and the number of them */

void read_file(const char* file_name, char** file_content);

void read_file_line_by_line(const char* file_name); /* first moving on source code, read row after row in order to build the symbol table */

bool line_is_empty(const char* line);

static char* tokens[MAX_TOKENS_IN_LINE] = {NULL}; /* constant structure {label, instruction, operand1, operand2} . if element not exist put NULL*/

static int tokens_arr_index = 0;

void line_analysis(const char* line);

bool tokens_processing(const char* token[]);

#endif
