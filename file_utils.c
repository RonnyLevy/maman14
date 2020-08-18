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
   		
   		has_symbol = true;
   		
   		tokens[tokens_arr_index] = token; 		
   	}
   	else
   	{
   		tokens[tokens_arr_index] = NULL;
   	}  	
   	
   	tokens_arr_index++;
   	
	/* get the other tokens in line */	 
	
	if (!has_symbol)
	{
		token = strtok(src_line, " , ");
		
		/*printf("token = %s\n", token);*/
		
		if (token != NULL)
		{
			tokens[tokens_arr_index] = token;
			
			tokens_arr_index++;
		}
	}
	
	while (token != NULL)
	{
		token = strtok(NULL, " ,");
			
		/*printf("token = %s\n", token);*/
		
		if (token != NULL)
		{
			tokens[tokens_arr_index] = token;
		
			tokens_arr_index++;
		}
	}
	
	/* is this line is string / data guidance ? */

	tokens_processing(tokens);	
	
	
	
	/* in the end, clear all for next line */
	
	int clr_index = 0;
	
	for ( ; clr_index < tokens_arr_index ; clr_index++)	tokens[clr_index] = NULL;
	
	has_symbol = false;  
	
	tokens_arr_index = 0;
}
 
bool tokens_processing(const char* token[])
{
	char* label_name  = token[0];
	
	char* instruction = token[1];
	
	char* operand1    = token[2];
	
	char* operand2    = token[3];
	
	label new_label;
	
	label* new_label_ptr = &new_label; /* for filling label (if exist) */
	
	/* first, check instruction type */
	
	if (!strcmp(instruction, data_guidance))
	{
		if (operand1 == NULL && operand2 == NULL)
		{
			printf("%s in line %d\n", data_guidance_no_operand, line_number);
			
			exit(-1);
		}
		
		if (operand1 != NULL) 
		{
			int val = atoi(operand1);
			
			if (val == 0)
			{
				printf("%s in line %d\n", data_guidance_invalid_number, line_number);
				
				exit(-1);
			}
			
			word tmp = (word){val};
			
			*(dc + dc_index) = tmp;
			
			dc_index++;
		}
	}
	else if (!strcmp(instruction, string_guidance))
	{
		if (operand1 == NULL && operand2 == NULL)
		{
			printf("%s in line %d\n", string_guidance_no_operand, line_number);
			
			exit(-1);
		}
		
		/* get all characters in put them into dc array */
		
		int str_idx = 0;
		
		
	}
	
		
	if (!is_instruction_valid(instruction))
	{
		printf("%s in line %d\n", invalid_instruction, line_number);
		
		exit(-1);
	}
	
	if (has_symbol)
	{	
		/* check if this label already exist in symbol table */
			
		bool exist = is_label_exist_in_symbol_table(label_name);
			
		if (!exist)
		{	
			/* append the the new table to symbol table */
				
			label new_label = {label_name, *ic, ".data"};
				
			*(symbol_table_ptr + symbol_table_idx) = new_label;
				
			symbol_table_idx++;
		}
	}
	

	/* now check the token type */
	
	
	else if (!strcmp(instruction, entry_guidance) || !strcmp(instruction, extern_guidance))
	{
		
	} 

	/* identify instruction type */	

	

	/* know instruction */ 		
	
		
}

