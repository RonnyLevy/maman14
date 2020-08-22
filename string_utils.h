#ifndef __string_utils_h__

#define __string_utils_h__

#include "string.h"

typedef enum { false, true } bool;

static char tmp_str[10]; /* for memcpy according to index */

bool is_string_empty(const char* str);

char* get_substring_after_first_char(const char* operand);

bool is_string_int_num(const char* str);

void remove_trailing_spaces(char* str);

#endif
