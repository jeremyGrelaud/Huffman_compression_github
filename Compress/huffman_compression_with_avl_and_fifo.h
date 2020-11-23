#ifndef HUFFMAN_COMPRESSION_WITH_AVL_AND_FIFO_H_INCLUDED
#define HUFFMAN_COMPRESSION_WITH_AVL_AND_FIFO_H_INCLUDED

#include "../preprocessor_directives_and_structures.h"

typedef struct Queue {
    Element* data_queue;
}Queue;

Queue* create_queue();
int is_empty(Queue* q);
int isSizeOne(Queue* q);
void enqueue(Queue* q, Node* new_node);
Node* dequeue(Queue* q);
Node* findMin(Queue* firstQueue, Queue* secondQueue);
Node* create_huffman_tree_FIFO(Node** tab, int size_tab);



#endif // HUFFMAN_COMPRESSION_WITH_AVL_AND_FIFO_H_INCLUDED