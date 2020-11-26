#ifndef HUFFMAN_COMPRESSION_WITH_AVL_AND_FIFO_H_INCLUDED
#define HUFFMAN_COMPRESSION_WITH_AVL_AND_FIFO_H_INCLUDED

#include "../preprocessor_directives_and_structures.h"


Queue* create_queue();
int is_empty(Queue* q);
int isSizeOne(Queue* q);
void enqueue(Queue* q, Node* new_node);
Node* dequeue(Queue* q);
Node* findMin(Queue* firstQueue, Queue* secondQueue);
Node* create_huffman_tree_FIFO(Node** tab, int size_tab);

Node_AVL* create_node_avl(int ascii, char* huffman_code,int taille);
void add_node_bst(Node_AVL** tree, Node_AVL* new_node);
void add_node_avl(Node_AVL** tree, Node_AVL* new_node);
int depth_AVL(Node_AVL* tree);
int balance_factor(Node_AVL* tree);
void r_rot(Node_AVL** tree);
void l_rot(Node_AVL** tree);
void trees_balance_BST(Node_AVL** tree);

void build_dico_and_avl(Node* huffman_tree, Node_AVL** avl_tree, FILE* compress, char arr[], int top);
void print_tree_infixe_avl(Node_AVL* tree);

char* traversal_avl(Node_AVL* tree, int actualCharacter);
void huffman_compression_in_same_file_with_xfactor_avl(FILE* text_to_convert, FILE* compress, Node_AVL* huffman_avl);
void compression_avl(FILE* text_to_convert, FILE* compress, char* texte_path, char* compress_path);
void free_tree_avl(Node_AVL* tree);

#endif // HUFFMAN_COMPRESSION_WITH_AVL_AND_FIFO_H_INCLUDED