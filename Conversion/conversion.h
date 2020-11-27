#ifndef CONVERSION_H_INCLUDED
#define CONVERSION_H_INCLUDED

/**
 * @brief Convert an integer in base octet.
 *      \n Example :
 *          \code (.c)
 *           convert_10_to_base_octet(actualCharact, 2, charact_convert);
 *          \endcode  
 * @param number The number.
 * @param base The base.
 * @param numberInBinary The number in binary base.
 */
void convert_10_to_base_octet(int number, int base, unsigned char* numberInBinary);

/**
 * @brief Convert an octet in base 10.
 *      \n Example :
 *          \code (.c)
 *           charactAscii = convert_octet_to_base_10(binary_number, 2);
 *          \endcode 
 * @param numberInBinary The number in binary.
 * @param base The base.
 * @return int The integer.
 */
int convert_octet_to_base_10(unsigned char* numberInBinary, int base);

/**
 * @brief Convert a file in binary.
 *      \n Example :
 *          \code (.c)
 *           convert_file_in_binary(text_to_convert, non_compress, path, non_compress_path);
 *          \endcode  
 * @param text The text we will convert.
 * @param text_in_binary The text converted.
 * @param path The path of the converted text.
 * @param non_compress_path The path of the text we will convert.
 */
void convert_file_in_binary(FILE* text, FILE* text_in_binary, char* path, char* non_compress_path);

/**
 * @brief Convert a text in binary in a text with character.
 *      \n Example :
 *          \code (.c)
 *           convert_binary_in_file(text_to_convert, non_compress, path, non_compress_path);
 *          \endcode   
 * @param text_in_binary The text we will convert.
 * @param text_convert The text converted.
 * @param non_compress_path The path of the converted text.
 * @param non_compress_decompress_path The path of the text we will convert.
 */
void convert_binary_in_file(FILE* text_in_binary, FILE* text_convert, char* non_compress_path,  char* non_compress_decompress_path);

#endif // CONVERSION_H_INCLUDED
