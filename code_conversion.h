#ifndef CODE_CONVERSION_H
#define CODE_CONVERSION_H

unsigned short build_word(const char *opcode, const char *src, const char *dest);
char *short_to_special_base4(unsigned short value);


#endif
