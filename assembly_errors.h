#ifndef __assembly_errors_h__

#define __assembly_errors_h__

static const char no_file[] = "ERROR:: no input file";

static const char no_assembly_file[] = "ERROR:: the input files without asm extension";

static const char label_already_exist[] = "ERROR:: label already exist";

static const char label_spaces_error[]  = "ERROR:: label contain spaces";

static const char invalid_instruction[] = "ERROR:: invalid instruction";

static const char data_guidance_no_first_argument[] = "ERROR:: must be first argument in data guidance";

static const char data_guidance_invalid_number[] = "ERROR:: data guidance must contain valid string num";

static const char string_guidance_operand[] = "ERROR:: must be exactly one argument for string guidance in first operand";

static const char immediate_addressing_error[] = "ERROR:: immediate addressing must contain integar number after #"; 

static const char mov_arguments_error[] = "ERROR:: mov command requires two arguments";

static const char mov_immediate_error[] = "ERROR:: mov immediate addressing must contain integar number after #";

static const char mov_src_addressing_error[] = "ERROR:: mov command requires only immediate, direct and register direct for source addressing";

static const char mov_dst_addressing_error[] = "ERROR:: mov command requires only direct or register direct for destination addressing";

static const char cmp_arguments_error[] = "ERROR:: cmp command requires two arguments";

static const char cmp_src_addressing_error[] = "ERROR:: cmp command requires only immediate, direct and register direct for source addressing";

static const char cmp_dst_addressing_error[] = "ERROR:: cmp command requires only immediate, direct and register direct for destination addressing";

static const char add_src_addressing_error[] = "ERROR:: add command requires only immediate, direct and register direct for source addressing";

static const char add_dst_addressing_error[] = "ERROR:: add command requires only direct and register direct for destination addressing";

static const char add_arguments_error[] = "ERROR:: add command requires two arguments";

static const char sub_src_addressing_error[] = "ERROR:: sub command requires only immediate, direct and register direct for source addressing";

static const char sub_dst_addressing_error[] = "ERROR:: sub command requires only direct and register direct for destination addressing";

static const char sub_arguments_error[] = "ERROR:: sub command requires two arguments";

static const char lea_src_addressing_error[] = "ERROR:: lea command requires only direct for source addressing";

static const char lea_dst_addressing_error[] = "ERROR:: lea command requires only direct and register direct for destination addressing";

static const char lea_arguments_error[] = "ERROR:: lea arguments not valid";

static const char clr_dst_addressing_error[] = "ERROR:: clr command requires only direct and register direct for destination addressing";

static const char clr_argument_error[] = "ERROR:: clr arguments not valid";

static const char not_dst_addressing_error[] = "ERROR:: not command requires only direct and register direct for destination addressing";

static const char not_argument_error[] = "ERROR:: not arguments not valid";

static const char inc_dst_addressing_error[] = "ERROR:: inc command requires only direct and register direct for destination addressing";

static const char inc_argument_error[] = "ERROR:: in arguments not valid";

static const char dec_dst_addressing_error[] = "ERROR:: dec command requires only direct and register direct for destination addressing";

static const char dec_argument_error[] = "ERROR:: dec arguments not valid";

static const char jmp_dst_addressing_error[] = "ERROR:: jmp command requires only direct and relative for destination addressing";

static const char jmp_argument_error[] = "ERROR:: jmp arguments not valid";

static const char bne_dst_addressing_error[] = "ERROR:: bne command requires only direct and relative for destination addressing";

static const char bne_argument_error[] = "ERROR:: bne arguments not valid";

static const char jsr_dst_addressing_error[] = "ERROR:: jsr command requires only direct and relative for destination addressing";

static const char jsr_argument_error[] = "ERROR:: jsr arguments not valid";

static const char red_dst_addressing_error[] = "ERROR:: red command requires only direct and register direct for destination addressing";

static const char red_argument_error[] = "ERROR:: red arguments not valid";

static const char prn_dst_addressing_error[] = "ERROR:: prn command requires only immediate, direct and register direct for destination addressing";

static const char prn_argument_error[] = "ERROR:: prn arguments not valid";

static const char rts_src_addressing_error[] = "ERROR:: rts command not requires source operand";

static const char rts_dst_addressing_error[] = "ERROR:: rts command not requires destination operand";

static const char rts_argument_error[] = "ERROR:: rts arguments not valid";

static const char stop_src_addressing_error[] = "ERROR:: stop command not requires source operand";

static const char stop_dst_addressing_error[] = "ERROR:: stop command not requires destination operand";

static const char stop_argument_error[] = "ERROR:: rts arguments not valid";

static const char no_legal_command[] = "ERROR:: illegal command";

static const char general_syntax_error[] = "ERROR:: syntax error";

#endif 
