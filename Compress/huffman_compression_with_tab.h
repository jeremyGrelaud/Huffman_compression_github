#ifndef HUFFMAN_COMPRESSION_WITH_TAB_H_INCLUDED
#define HUFFMAN_COMPRESSION_WITH_TAB_H_INCLUDED

#include "../preprocessor_directives_and_structures.h"

/**
 * @brief Create a node object.
 *      \n Example :
 *          \code (.c)
 *           Node* new_node = create_node(i, tabFrequencies[i], NULL, NULL);
 *          \endcode   
 * @param ascii Code ascii.
 * @param frequency The frequency.
 * @param leftp The left child.
 * @param rightp The right child.
 * @return Node* The Node created.
 */
Node* create_node(int ascii, int frequency, Node* leftp, Node* rightp);

/**
 * @brief Free a tree.
 *      \n Example :
 *          \code (.c)
 *           free_tree(huffman_tree);
 *          \endcode  
 * @param tree The root of the tree.
 */
void free_tree(Node* tree);

/**
 * @brief Count the frequencies of each character present in a File and stock them in an array.
 *      \n Example :
 *          \code (.c)
 *           tab = frequencies(text_to_convert);
 *          \endcode   
 * @param fichier The file.
 * @return int* An array with all the frequencies.
 */
int* frequencies(FILE* fichier);

/**
 * @brief Create a Huffman tree via the frequencies.
 *      \n Example :
 *          \code (.c)
 *           Node* huffman_tree = build_huffman_tree(tab);
 *          \endcode  
 * @param tabFrequencies The array with the frequencies.
 * @return Node* The Node of the Huffman tree.
 */
Node* build_huffman_tree(int* tabFrequencies);

/**
 * @brief sorts the linked list by changing next pointers (not data).
 *      \n Example :
 *          \code (.c)
 *           MergeSort(&head);
 *          \endcode  
 * @param headRef The list.
 * @return * void 
 */ 
void MergeSort(Element** headRef);
Element* SortedMerge(Element* a, Element* b);

/**
 * @brief Remove the first Element of a list.
 *      \n Example :
 *          \code (.c)
 *           temp1 = remove_first_elem(&head);
 *          \endcode 
 * @param head The first Element.
 * @return Element* The new first Element.
 */
Element* remove_first_elem(Element** head);

/**
 * @brief Create a huffman tree from LSC object.
 *      \n Example :
 *          \code (.c)
 *           huffman_tree = create_huffman_tree_from_LSC(new_elem);
 *          \endcode  
 * @param head The first Element of the list.
 * @return Node* The root of the Huffman tree.
 */
Node* create_huffman_tree_from_LSC(Element* head);

/**
 * @brief Count the depth of a tree.
 *      \n Example :
 *          \code (.c)
 *           int depth_huffman_tree = depth(huffman_tree);
 *          \endcode  
 * @param tree The tree analyzed.
 * @return int The depth of the tree.
 */
int depth(Node* tree);

/**
 * @brief Build a dictionary from a tree.
 *      \n Example :
 *          \code (.c)
 *           build_dico(huffman_tree, tabDictionary, arr, 0);
 *          \endcode  
 * @param tree The tree used to create the dictionary.
 * @param tabDictionary The character of the dictionary.
 * @param arr Thee tab with binary code of each character.
 * @param top A counter.
 */
void build_dico(Node* tree, char** tabDictionary, unsigned char arr[], int top);

/**
 * @brief Compress a file in an other file.
 *      \n Example :
 *          \code (.c)
 *           huffman_compression_in_same_file_with_xfactor(text_to_convert, compress, tabDictionary);
 *          \endcode 
 * @param text_to_compress File with the text we need to compress.
 * @param compress File with the text compress.
 * @param tabDictionary The dictionary in the dile with the text compress.
 */
void huffman_compression_in_same_file_with_xfactor(FILE* text_to_compress, FILE* compress, char** tabDictionary);

/**
 * @brief Create a huffman tree based on the dictionary.
 *      \n Example :
 *          \code (.c)
 *           new_huffman_tree = create_huffman_tree_from_dictionary(compress);
 *          \endcode  
 * @param compress The compress files with, in first line, the dictionary.
 * @return Node* The created Node of the huffman tree.
 */
Node* create_huffman_tree_from_dictionary(FILE* compress);

/**
 * @brief Decompress a file in an other fil via a tree.
 *      \n Example :
 *          \code (.c)
 *           huffman_decompression_with_xfactor(new_huffman_tree, compress, decompress);
 *          \endcode 
 * @param tree The Huffman tree.
 * @param compress The compressed file.
 * @param decompress The decompressed file.
 */
void huffman_decompression_with_xfactor(Node* tree, FILE* compress, FILE* decompress);

/**
 * @brief Print a tree in the prefixe order.
 *      \n Example :
 *          \code (.c)
 *           print_tree_prefixe(tree->left);
 *          \endcode  
 * @param tree The tree printed.
 */
void print_tree_prefixe(Node* tree);

/**
 * @brief Print a list.
 *      \n Example :
 *          \code (.c)
 *           printList(head);
 *          \endcode 
 * @param debut The first Element of the list.
 */
void printList(Element* debut);

/**
 * @brief Compress the file with the path of each file : the one we compress and the compressed one.
 *      \n Example :
 *          \code (.c)
 *           compression(text_to_convert, compress, path, compress_path);
 *          \endcode  
 * @param text_to_convert The file we compress.
 * @param compress The compressed file.
 * @param texte_path The path of the file we compress.
 * @param compress_path The path of the compressed file.
 */
void compression(FILE* text_to_convert, FILE* compress, char* texte_path, char* compress_path);

/**
 * @brief Decompress the file with the path of each file : the one we decompress and the decompressed one.
 *      \n Example :
 *          \code (.c)
 *           decompression(compress, decompress, compress_path, decompress_path);
 *          \endcode   
 * @param compress The file we decompress.
 * @param decompress The decompressed file.
 * @param compress_path The path of the file we decompress.
 * @param decompress_path The path of the decompressed file.
 */
void decompression(FILE* compress, FILE* decompress, char* compress_path, char* decompress_path);

#endif // HUFFMAN_COMPRESSION_WITH_TAB_H_INCLUDED
