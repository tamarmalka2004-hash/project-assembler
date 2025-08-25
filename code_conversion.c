#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "code_conversion.h"


/*
* Builds a 10-bit machine code word based on opcode, source operand, and destination operand.
* Encoding layout (bit positions):
* [9-6] - opcode (4 bits)
* [5-4] - source addressing mode (2 bits)
* [3-2] - destination addressing mode (2 bits)
* [1-0] - ARE bits (2 bits) – default to 2 (Relocatable) for now
*/
unsigned short build_word(const char *opcode, const char *src, const char *dest) {
unsigned short result = 0;
int op_index = 0, src_type = 0, dest_type = 0;


while (op_index < 16 && strcmp(opcode, opcodes[op_index]) != 0) op_index++;
result |= (op_index & 0xF) << 6; /* opcode bits (4 bits) at bits 6-9 */


if (is_number(src)) src_type = 1;
else if (is_register(src)) src_type = 3;
else if (is_valid_label(src)) src_type = 2;
result |= (src_type & 0x3) << 4; /* src addressing (2 bits) at bits 4-5 */


if (is_number(dest)) dest_type = 1;
else if (is_register(dest)) dest_type = 3;
else if (is_valid_label(dest)) dest_type = 2;
result |= (dest_type & 0x3) << 2; /* dest addressing (2 bits) at bits 2-3 */


result |= 2; /* ARE bits (2 bits) set to 10 for Relocatable */


return result & 0x3FF; /* Mask to ensure only 10 bits are returned */
}


/* Converts a 10-bit number to a special base-4 representation */
char *short_to_special_base4(unsigned short value) {
char *result = (char *)malloc(6); /* 5 chars + null terminator */
int i;
char base4_chars[] = { 'a', 'b', 'c', 'd' }; /* Custom base-4 encoding */
if (!result) return NULL;


result[5] = '\0';
for (i = 4; i >= 0; i--) {
result[i] = base4_chars[value % 4];
value /= 4;
}


return result;
}
