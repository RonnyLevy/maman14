#include <stdlib.h>
#include <string.h> 
#include "file_utils.h"
#include "language_structure.h"

const char* get_file_extension(char* file)
{
	const char* dot; /* file extension */
	
	dot = strrchr(file, '.');
	
	if (!dot || dot == file) {return "";}
	
	return dot + 1;
}

bool extension_validation(char* arguments[], const int num)
{     
	bool valid = false;

	char* file_extension;

	int i = 1;

	for ( ; i < num ; i++) /* skip over elf name and take the first argument*/
	{	
		file_extension = get_file_extension(*(arguments + i));

		if (file_extension == "") {return false;}
		
		if (strcmp(file_extension, ASM)) 
		{
			valid = false;
		
			return valid;
		}
		
		valid = true;			
	}
	
	return valid;
}

void read_file(const char* file_name, char** dest_file)
{
	FILE *fp; 
	
	long size;
	
	fp = fopen(file_name, "r"); 
	
	if (!fp)
	{
		*dest_file = NULL;
		
		return;
	}
	 
	fseek(fp, 0, SEEK_END); 
	
	size = ftell(fp); 
	
	if (size == 0)
	{
		*dest_file = NULL;
		
		return;
	}	
	
	fseek(fp, 0, SEEK_SET);
	
	*dest_file = (char*)malloc(sizeof(char) * (size + 1));
	
	if (*dest_file == NULL)
	{
		return;
	}
	
	fread(*dest_file, size, 1, fp);
	
	fclose(fp);			
}

void read_file_line_by_line(const char* file_name)
{
  	ssize_t line_buf_size = 0;
  
  	int line_size = 0;
  
  	FILE* fp = fopen(file_name, "r");
  
  	if (!fp) { return; }  	

	char* buff = NULL;	

    while (line_size >= 0)
  	{    
	    line_size = getline(&buff, &line_buf_size, fp); 

		/* check if line is empty */
		
		if (!line_is_empty(buff))
		{
			if (line_size > 0 && (*buff != comment)) 
			{
				strcpy(line_buffer, buff); /* for line_analysis function below : strtok gets char array */
			
				/*printf("line = %s\n", line_buffer);
				
				/* check if this line contain label */
				
				line_analysis(line_buffer);	    	
			} 
		}
		
		line_number++;
  	}
  
  	/* file end */
  
  	fclose(fp);
}

bool line_is_empty(const char* line)
{
	while (*line != '\0')
	{
		if (!isspace(*line)) return false;
		
		line++;
	}
	
	return true;
}

void line_analysis(const char* line)
{	
	printf("=============================\n");

	const char colon[2] = ":";
   	
   	char* token;
   
   	strcpy(src_line, line); /* after strtok calling, original string (line) changes */
   
   	printf("source line = %s\n", line);
   
    /* first, try to find label */
   
    token = strtok(line, colon);
   
   	printf("label = %s\n", token);
   
   	if (strcmp(token, src_line)) 
   	{
   		/* found label */
   		
   		printf("found label\n");
   		
   		has_symbol = true;
   		
   		tokens[tokens_arr_index] = token; 		
   	}
   	else
   	{
   		tokens[tokens_arr_index] = NULL; /* remember the structure: tokens[0] - label, tokens[1] - instruction, tokens[2] - 										operand1 , tokens[3] - operand2. if not exist - NULL */
   	}  	
   	
   	tokens_arr_index++;
   	
	/* get the other tokens in line */	 
	
	if (!has_symbol)
	{
		token = strtok(src_line, " \t, ");
		
		/*printf("#### token = %s\n", token);*/
		
		if (token != NULL)
		{
			tokens[tokens_arr_index] = token;
			
			tokens_arr_index++;
		}
	}
	
	while (token != NULL)
	{
		token = strtok(NULL, " \t,");
			
		/*printf("@@@@ token = %s\n", token);*/
		
		if (token != NULL)
		{
			tokens[tokens_arr_index] = token;
		
			tokens_arr_index++;
		}
	}
	
	int idx = 0;
	
	for ( ; idx <  tokens_arr_index ; idx++) printf("loop:: token = %s\n", tokens[idx]);
	
	/*tokens_processing(tokens);	
	
	/* in the end, clear all for next line */
	
	int clr_index = 0;
	
	for ( ; clr_index < tokens_arr_index ; clr_index++)	tokens[clr_index] = NULL;
	
	has_symbol = false;  
	
	tokens_arr_index = 0;
}
 
bool tokens_processing(const char* token[])
{
	char* label_name  = token[0];
	
	char* command     = token[1];
	
	char* operand1    = token[2];
	
	char* operand2    = token[3];
	
	label new_label;
	
	label* new_label_ptr = &new_label; /* for filling label (if exist) */
	
	/* The most important token now is token[1]. try to identify which kind of type instruction is.
	
	   There are three posibilities options: 
	   
	   A) guidance command (.data / .code).
	   
	   B) instruction command (mov, add, inc etc ..).
	   
	   C) something else (illegal). 
	
	*/
	
	if (!strcmp(command, data_guidance))
	{
		if (has_symbol)
		{
			/* check if this label already exist in symbol table */
			
			bool exist = is_label_exist_in_symbol_table(label_name);
			
			if (!exist)
			{	
				/* append the the new table to symbol table */
				
				label new_label = {label_name, *dc, data_guidance};
				
				*(symbol_table_ptr + symbol_table_idx) = new_label;
				
				symbol_table_idx++;
			}
		}
	
		parse_data_guidance_operands(operand1, operand2);
	}
	else if (!strcmp(command, string_guidance))
	{
		if (has_symbol)
		{
			/* check if this label already exist in symbol table */
			
			bool exist = is_label_exist_in_symbol_table(label_name);
			
			if (!exist)
			{	
				/* append the the new table to symbol table */
				
				label new_label = {label_name, *dc, string_guidance};
				
				*(symbol_table_ptr + symbol_table_idx) = new_label;
				
				symbol_table_idx++;
			}
		}
	
		parse_string_guidance_operands(operand1, operand2);
	}
	else if (!is_instruction_valid(command, operand1, operand2)) 
	{
		printf("%s in line %d\n", invalid_instruction, line_number);
		
		exit(-1);
	}
	else
	{
		
	}
/*		
	else if (!strcmp(command, entry_guidance) || !strcmp(command, extern_guidance))
	{
		
	} 
	*/	
}

