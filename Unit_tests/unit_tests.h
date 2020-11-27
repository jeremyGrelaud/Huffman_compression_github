/********************************************************//**
 * @file unit_tests.h
 * @author Jeremy GRELAUD, Amaury ROSSIGNOL.
 * @brief Regroup all the units tests.
 * @version 0.1
 * @date 2020-11-27
 * 
 * @copyright Copyright (c) 2020
 * 
 ***********************************************************/
#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include "../Compress/huffman_compression_with_tab.h"
#include "../preprocessor_directives_and_structures.h"

int number_of_caracters(FILE*);

int TU_convert_10_to_base_octet();
int compare(Node*, Node*);
int TU_create_huffman_tree_from_LSC();
int TU_frequencies();
int TU_decompression(Node* new_huffman_tree, FILE* compress, FILE* decompress, FILE* original_file);
int TU_build_dico();
int TU_build_dico_and_avl();
int compare_AVL(Node_AVL*,Node_AVL*);

int For_rule_them_all(int);
void Test(FILE*, FILE*, FILE*, FILE*, char*, char*, char*, char*);
void Test_without_non_compress(FILE*, FILE*, FILE*, char*, char*, char*);

#endif //UNIT_TESTS_H
