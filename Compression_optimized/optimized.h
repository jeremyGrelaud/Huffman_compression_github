#ifndef OPTIMIZED_H_INCLUDED
#define OPTIMIZED_H_INCLUDED

#include "../preprocessor_directives_and_structures.h"

void build_dico(Node* root, FILE* dico, int arr[], int top);
void huffman_compression_in_different_file(FILE* text_to_compress, FILE* dico, FILE* compress, int depth_huffman_tree);
void huffman_compression_in_same_file(FILE* text_to_compress, FILE* compress, int depth_huffman_tree);

Node* create_node(int ascii, int frequency);
Node* create_huffman_tree_by_dicodicodi(FILE* dico);
void decompression(Node* tree, FILE* compress, FILE* decompress);

#endif // OPTIMIZED_H_INCLUDED
