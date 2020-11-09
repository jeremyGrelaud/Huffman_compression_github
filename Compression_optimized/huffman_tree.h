#ifndef HUFFMAN_TREE_H_INCLUDED
#define HUFFMAN_TREE_H_INCLUDED

#include "../preprocessor_directives_and_structures.h"

int number_of_caracters(FILE* fichier);
void trees_free_tree(Node** tree);
void permut(Node** x, Node** y);
void list_bubble_sort(Node** tab, int taille);

int* frequencies(FILE* fichier);
Node* build_huffman_tree(int* tabFrequencies);
void print_tree_prefixe(Node* tree);

void printList(Element* debut);
void bubbleSort(Element* start);
void swape(Element* a, Element* b);
Element* remove_first_elem(Element** head);
Node* create_huffman_tree_from_LSC(Element* head);

int depth(Node* tree);

#endif // HUFFMAN_TREE_H_INCLUDED
