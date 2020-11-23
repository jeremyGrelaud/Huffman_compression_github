#ifndef HUFFMAN_COMPRESSION_WITH_TAB_H_INCLUDED
#define HUFFMAN_COMPRESSION_WITH_TAB_H_INCLUDED

#include "../preprocessor_directives_and_structures.h"

Node* create_node(int ascii, int frequency, Node* leftp, Node* rightp);
void free_tree(Node* tree);

int* frequencies(FILE* fichier);
Node* build_huffman_tree(int* tabFrequencies);

void MergeSort(Element** headRef);
Element* SortedMerge(Element* a, Element* b);
Element* remove_first_elem(Element** head);
Node* create_huffman_tree_from_LSC(Element* head);

int depth(Node* tree);

void build_dico(Node* tree, char** tabDictionary, unsigned char arr[], int top);
void huffman_compression_in_same_file_with_xfactor(FILE* text_to_compress, FILE* compress, char** tabDictionary);
Node* create_huffman_tree_from_dictionary(FILE* compress);
void huffman_decompression_with_xfactor(Node* tree, FILE* compress, FILE* decompress);

void print_tree_prefixe(Node* tree);
void printList(Element* debut);

void compression(FILE* text_to_convert, FILE* compress, char* texte_path, char* compress_path);
void decompression(FILE* compress, FILE* decompress, char* compress_path, char* decompress_path);

#endif // HUFFMAN_COMPRESSION_WITH_TAB_H_INCLUDED
