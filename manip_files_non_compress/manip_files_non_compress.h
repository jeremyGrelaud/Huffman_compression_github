#ifndef MANIP_FILES_NON_COMPRESS_H_INCLUDED
#define MANIP_FILES_NON_COMPRESS_H_INCLUDED

void convert_10_to_base_octet(int number, int base, char* numberInBinary);
int convert_octet_to_base_10(char* numberInBinary, int base);

void convert_file_in_binary(FILE* text, FILE* text_in_binary);
void convert_binary_in_file(FILE* text_in_binary, FILE* text_convert);

#endif // MANIP_FILES_NON_COMPRESS_H_INCLUDED