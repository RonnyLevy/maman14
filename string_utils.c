#include "string_utils.h"

bool is_string_empty(const char* str)
{
	while (*str != '\0')
	{
		if (!isspace(*str)) return false;
		
		str++;
	}
	
	return true;
}

char* get_substring_after_first_char(const char* operand)
{
	char* substring;

	memcpy(substring, operand + 1, strlen(operand));
	
	return substring;
}

bool is_string_int_num(const char* str)
{
	if (str == NULL || is_string_empty(str)) return false;

	int len = strlen(str);
	
	int idx = 0;
	
	for ( ; idx < len ; idx++)
	{
		if (!isdigit(*(str + idx))) return false;
	}
	
	return true;
}
