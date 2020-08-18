#ifndef __assembly_errors_h__

#define __assembly_errors_h__

static const char label_already_exist[] = "ERROR:: label already exist";

static const char label_spaces_error[]  = "ERROR:: label contain spaces";

static const char invalid_instruction[] = "ERROR:: invalid instruction";

static const char data_guidance_no_operand[] = "ERROR:: must be at least one argument for data guidance";

static const char data_guidance_invalid_number[] = "ERROR:: data guidance must contain valid string num";

static const char string_guidance_no_operand[] = "ERROR:: must be at least one argument for string guidance";

static const char mov_arguments_error[] = "ERROR:: mov command requires two arguments";

static const char mov_src_addressing_error[] = "ERROR:: mov command requires only immediate, direct and register direct for source addressing";

static const char cmp_src_addressing_error[] = "ERROR:: cmp command requires only immediate, direct and register direct for source addressing";

static const char cmp_dst_addressing_error[] = "ERROR:: cmp command requires only immediate, direct and register direct for destination addressing";

static const char add_src_addressing_error[] = "ERROR:: add command requires only immediate, direct and register direct for source addressing";

static const char add_dst_addressing_error[] = "ERROR:: add command requires only direct and register direct for destination addressing";

static const char sub_src_addressing_error[] = "ERROR:: sub command requires only immediate, direct and register direct for source addressing";

static const char sub_dst_addressing_error[] = "ERROR:: sub command requires only direct and register direct for destination addressing";

static const char lea_src_addressing_error[] = "ERROR:: lea command requires only direct for source addressing";

static const char lea_dst_addressing_error[] = "ERROR:: lea command requires only direct and register direct for destination addressing";

static const char clr_src_addressing_error[] = "ERROR:: clr command not requires source operand";

static const char clr_dst_addressing_error[] = "ERROR:: clr command requires only direct and register direct for destination addressing";

static const char not_src_addressing_error[] = "ERROR:: not command not requires source operand";

static const char not_dst_addressing_error[] = "ERROR:: not command requires only direct and register direct for destination addressing";

static const char inc_src_addressing_error[] = "ERROR:: inc command not requires source operand";

static const char inc_dst_addressing_error[] = "ERROR:: inc command requires only direct and register direct for destination addressing";

static const char dec_src_addressing_error[] = "ERROR:: dec command not requires source operand";

static const char dec_dst_addressing_error[] = "ERROR:: dec command requires only direct and register direct for destination addressing";

static const char jmp_src_addressing_error[] = "ERROR:: jmp command not requires source operand";

static const char jmp_dst_addressing_error[] = "ERROR:: jmp command requires only direct and relative for destination addressing";

static const char bne_src_addressing_error[] = "ERROR:: bne command not requires source operand";

static const char bne_dst_addressing_error[] = "ERROR:: bne command requires only direct and relative for destination addressing";

static const char jsr_src_addressing_error[] = "ERROR:: jsr command not requires source operand";

static const char jsr_dst_addressing_error[] = "ERROR:: jsr command requires only direct and relative for destination addressing";

static const char red_src_addressing_error[] = "ERROR:: red command not requires source operand";

static const char red_dst_addressing_error[] = "ERROR:: red command requires only direct and register direct for destination addressing";

static const char prn_src_addressing_error[] = "ERROR:: prn command not requires addressing for source";

static const char prn_dst_addressing_error[] = "ERROR:: prn command requires only immediate, direct and register direct for destination addressing";

static const char rts_src_addressing_error[] = "ERROR:: rts command not requires source operand";

static const char rts_dst_addressing_error[] = "ERROR:: rts command not requires destination operand";

static const char stop_src_addressing_error[] = "ERROR:: stop command not requires source operand";

static const char stop_dst_addressing_error[] = "ERROR:: stop command not requires destination operand";

static const char general_syntax_error[] = "ERROR:: syntax error";

#endif 
