/***********************************************************//**
 * @file path.h
 * @author Julien HASSOUN, Jeremy GRELAUD, Amaury ROSSIGNOL, Gauthier MARCELIN, Guillaume DUMAS.
 * @brief Regroup all the function to build path for the file.
 * @version 0.1
 * @date 2020-11-27
 * 
 * @copyright Copyright (c) 2020
 * 
 **************************************************************/
#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

/**
 * @brief Return 1 if there s only one type of char in the file or return 0 else.
 *      \n Example :
 *          \code (.c)
 *           else if(one_letter(test) == 1){
 *                  printf("It seems this file do exists, but only contains one different letter. It can't work. Try again ...\n");
 *                  continuer = 1;
 *              }
 *          \endcode  
 * @param file The file.
 * @return int Booleen.
 */
int one_letter(FILE* file);

/**
 * @brief Ask the path of a file.
 *      \n Example :
 *          \code (.c)
 *           if (ask_path(path) == 0){
 *              }
 *          \endcode 
 * @param path The file.
 * @return int 
 */
int ask_path(char* path);

/**
 * @brief Create a path for the compressed file. 
 *      \n Example :
 *          \code (.c)
 *           build_compress_path(path, compress_path);
 *          \endcode  
 * @param path The path of the file.
 * @param compress_path The path of the compressed file.
 */
void build_compress_path(char* path, char* compress_path);

/**
 * @brief Create a path for the decompressed file.
 *      \n Example :
 *          \code (.c)
 *           build_decompress_path(compress_path, decompress_path);
 *          \endcode  
 * @param compress_path The path of the compressed file.
 * @param decompress_path The path of the decompressed file.
 */
void build_decompress_path(char* compress_path, char* decompress_path);

/**
 * @brief Create a path for the non compressed file.
 *      \n Example :
 *          \code (.c)
 *           build_non_compress_path(path, non_compress_path);
 *          \endcode  
 * @param path The path of the file.
 * @param non_compress_path The path of the non compressed file.
 */
void build_non_compress_path(char* path, char* non_compress_path);

#endif // PATH_H_INCLUDED
