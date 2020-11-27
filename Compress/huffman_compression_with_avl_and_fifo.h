/*****************************************************************//**
 * @file huffman_compression_with_avl_and_fifo.h
 * @author Julien HASSOUN, Jérémy GRELAUD, Amaury ROSSIGNOL, Gauthier MARCELIN, Guillaume DUMAS.
 * @brief Regroup all the function to compress with an AVL and Queue.
 * @version 03.2
 * @date 2020-10-24
 * 
 * @copyright Copyright (c) 2020
 * 
 *********************************************************************/
#ifndef HUFFMAN_COMPRESSION_WITH_AVL_AND_FIFO_H_INCLUDED
#define HUFFMAN_COMPRESSION_WITH_AVL_AND_FIFO_H_INCLUDED

#include "../preprocessor_directives_and_structures.h"

/**
 * @brief Create a queue object.
 *      \n Example :
 *          \code (.c)
 *          Queue* firstQueue = create_queue();
 *          \endcode
 * @return The queue. 
 */
Queue* create_queue();

/**
 * @brief Check if a queue is empty or not.
 *      \n Example :
 *          \code (.c)
 *          if (is_empty(firstQueue))
 *              return dequeue(secondQueue);
 *          \endcode
 * @param q The queue.
 * @return int A booléen.
 */
int is_empty(Queue* q);

/**
 * @brief Check if the queue is at minimum size 1.
 *      \n Example :
 *          \code (.c)
 *          while (!(is_empty(firstQueue) && isSizeOne(secondQueue))) {
 *              left_node = findMin(firstQueue, secondQueue);
 *          \endcode
 * @param q The queue.
 * @return int A booléen.
 */
int isSizeOne(Queue* q);

/**
 * @brief Add a node at the end of the queue.
 *      \n Example :
 *          \code (.c)
 *          enqueue(secondQueue, top);
 *          \endcode
 * @param q The queue.
 * @param new_node The node added.
 */
void enqueue(Queue* q, Node* new_node);

/**
 * @brief Remove a node at the beginning.
 *      \n Example :
 *          \code (.c)
 *          if (is_empty(firstQueue))
 *              return dequeue(secondQueue);
 *          \endcode
 * @param q The queue.
 * @return Node* The node deleted.
 */
Node* dequeue(Queue* q);

/**
 * @brief Get the node with the lowest frequency from two queues.
 *      \n Example :
 *          \code (.c)
 *          left_node = findMin(firstQueue, secondQueue);
 *          \endcode 
 * @param firstQueue The first queue.
 * @param secondQueue The second queue.
 * @return Node* The node with the lowest frequency.
 */
Node* findMin(Queue* firstQueue, Queue* secondQueue);

/**
 * @brief Create a huffman tree from atab of node.
 *      \n Example :
 *          \code (.c)
 *          huffman_tree = create_huffman_tree_FIFO(tab2,nbcharacter);
 *          \endcode  
 * @param tab Tab of node.
 * @param size_tab The size of the tab.
 * @return Node* The root.
 */
Node* create_huffman_tree_FIFO(Node** tab, int size_tab);

/**
 * @brief Create a node avl object.
 *      \n Example :
 *          \code (.c)
 *          add_node_avl(avl_tree, create_node_avl(huffman_tree->ascii, arr, top));
 *          \endcode 
 * @param ascii The code ascii of the character.
 * @param huffman_code The huffman code.
 * @return Node_AVL* A node of the AVL.
 */
Node_AVL* create_node_avl(int ascii, char* huffman_code,int taille);

/**
 * @brief Add a node to a search binary tree.
 *      \n Example :
 *          \code (.c)
 *          add_node_bst(tree, new_node);
 *          \endcode 
 * @param tree The binary search tree.
 * @param new_node The new node.
 */
void add_node_bst(Node_AVL** tree, Node_AVL* new_node);

/**
 * @brief Add a node to an AVL.
 *      \n Example :
 *          \code (.c)
 *          add_node_avl(avl_tree, create_node_avl(huffman_tree->ascii, arr, top));
 *          \endcode  
 * @param tree The AVL.
 * @param new_node The new node.
 */
void add_node_avl(Node_AVL** tree, Node_AVL* new_node);

/**
 * @brief Count the depth of an AVL.
 *      \n Example :
 *          \code (.c)
 *          int left_depth = depth_AVL(tree->left);
 *          \endcode  
 * @param tree The AVL.
 * @return int The depth.
 */
int depth_AVL(Node_AVL* tree);

/**
 * @brief Give the balance factor of an AVL.
 *      \n Example :
 *          \code (.c)
 *          int bfact = balance_factor(*tree);
 *          \endcode  
 * @param tree The AVL.
 * @return int The balance factor.
 */
int balance_factor(Node_AVL* tree);

///right rotation
void r_rot(Node_AVL** tree);

///left rotation
void l_rot(Node_AVL** tree);

/**
 * @brief Balance an AVL via the balance factor.
 *      \n Example :
 *          \code (.c)
 *          trees_balance_BST(&((*tree)->left));
 *          \endcode 
 * @param tree The AVL.
 */
void trees_balance_BST(Node_AVL** tree);

/**
 * @brief Build a dico and an AVL via a huffman tree.
 *      \n Example :
 *          \code (.c)
 *           build_dico_and_avl(huffman_tree->left, avl_tree, compress, arr, top + 1);
 *          \endcode  
 * @param huffman_tree The huffman tree.
 * @param avl_tree The AVL we gonna build.
 * @param compress The dictionary we gonna build (empty file).
 * @param arr The tab of each character. 
 * @param top The size we increment.
 */
void build_dico_and_avl(Node* huffman_tree, Node_AVL** avl_tree, FILE* compress, char arr[], int top);

/**
 * @brief Print an AVL in the infixe order.
 *      \n Example :
 *          \code (.c)
 *           print_tree_infixe_avl(tree->right);
 *          \endcode  
 * @param tree The AVL.
 */
void print_tree_infixe_avl(Node_AVL* tree);

/**
 * @brief Run through the AVL to find the huffman code of the character.
 *      \n Example :
 *          \code (.c)
 *           fprintf(compress, "%s", traversal_avl(huffman_avl, actualCharacter));
 *          \endcode 
 * @param tree The AVL.
 * @param actualCharacter The character.
 * @return char* The huffman code.
 */
char* traversal_avl(Node_AVL* tree, int actualCharacter);

/**
 * @brief Compress in the file of the dictionary with the xfactor of the AVL.
 *      \n Example :
 *          \code (.c)
 *           huffman_compression_in_same_file_with_xfactor_avl(text_to_convert, compress, huffman_avl);
 *          \endcode  
 * @param text_to_compress The text we gonna compress.
 * @param compress The compressed text.
 * @param huffman_avl The AVL create via the huffman tree.
 */
void huffman_compression_in_same_file_with_xfactor_avl(FILE* text_to_convert, FILE* compress, Node_AVL* huffman_avl);

/**
 * @brief Compress a text to another file.
 *      \n Example :
 *          \code (.c)
 *           compression_avl(text_to_convert, compress, path, compress_path);
 *          \endcode  
 * @param text_to_convert The text we gonna compress.
 * @param compress The compressed text.
 * @param texte_path The path of the file we gonna compress.
 * @param compress_path The path of the compressed text.
 */
void compression_avl(FILE* text_to_convert, FILE* compress, char* texte_path, char* compress_path);

/**
 * @brief Free an AVL.
 *      \n Example :
 *          \code (.c)
 *           free_tree_avl(huffman_avl);
 *          \endcode   
 * @param tree The AVL.
 */
void free_tree_avl(Node_AVL* tree);

#endif // HUFFMAN_COMPRESSION_WITH_AVL_AND_FIFO_H_INCLUDED