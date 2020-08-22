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

void remove_trailing_spaces(char* str) 
{
	int index = -1;

    int i = 0;
    
    while (str[i] != '\0')
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }

        i++;
    }

    str[index + 1] = '\0';
}
