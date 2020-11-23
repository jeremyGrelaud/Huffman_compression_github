#ifndef CONVERSION_H_INCLUDED
#define CONVERSION_H_INCLUDED

void convert_10_to_base_octet(int number, int base, char* numberInBinary);
int convert_octet_to_base_10(char* numberInBinary, int base);

void convert_file_in_binary(FILE* text, FILE* text_in_binary);
void convert_binary_in_file(FILE* text_in_binary, FILE* text_convert);

#endif // CONVERSION_H_INCLUDED
