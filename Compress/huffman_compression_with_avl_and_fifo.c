#include <stdio.h>
#include <stdlib.h>

#include "huffman_compression_with_avl_and_fifo.h"

Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data_queue = NULL;
    return q;
}

int is_empty(Queue* q) {
    if (q->data_queue == NULL) {
        return 1; //there queue is empty
    }
    else {
        return 0;
    }
}

int isSizeOne(Queue* q) {
    if ((q->data_queue != NULL) && (q->data_queue->next == NULL)) {
        return 1;
    }
    else {
        return 0;
    }
}

//we add at the end and remove at the beginning = FIFO
void enqueue(Queue* q, Node* new_node) {
    //ajout à la fin
    Element* n_e = (Element*)malloc(sizeof(Element));
    n_e->data = new_node;
    n_e->next = NULL;

    if (is_empty(q) == 1) {
        q->data_queue = n_e;
    }
    else {
        Element* temp = q->data_queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        //temp is the actual last element
        temp->next = n_e;
    }
}

Node* dequeue(Queue* q) {
    //remove at the beginning
    if (is_empty(q) == 1) {
        return NULL;
    }
    else {
        Element* old = q->data_queue;
        q->data_queue = q->data_queue->next;//warning don't forget
        Node* temp = old->data;
        free(old);
        return temp;
    }
}


//A function to get the node with lowest frequency from two queues //
Node* findMin(Queue* firstQueue, Queue* secondQueue)
{
    // If first queue is empty, dequeue from
    // second queue
    if (is_empty(firstQueue))
        return dequeue(secondQueue);

    // If second queue is empty, dequeue from
    // first queue
    if (is_empty(secondQueue))
        return dequeue(firstQueue);

    else {
        // Else, compare the head of two queues and
        // dequeue minimum
        if (firstQueue->data_queue->data->frequenc < secondQueue->data_queue->data->frequenc)
            return dequeue(firstQueue);
        else {
            return dequeue(secondQueue);
        }
    }
}

// The main function that builds Huffman tree
Node* create_huffman_tree_FIFO(Node** tab, int size_tab)
{
    Node* left_node, * right_node, * top;

    // Step 1: Create two empty queues
    Queue* firstQueue = create_queue();
    Queue* secondQueue = create_queue();

    // Step 2: Enqueue all nodes in the first queue in a
    //growing order compared to frequencies
    for (int i = 0; i < size_tab; ++i)
        enqueue(firstQueue, tab[i]); //tab[i] contains a Node*

    // Run while Queues contain more than one node. Finally,
    // first queue will be empty and second queue will
    // contain only one node the root of the huffman tree
    while (!(is_empty(firstQueue) && isSizeOne(secondQueue))) {
        // Step 3: Dequeue the two nodes with the minimum
        // frequency by examining the head of both queues
        left_node = findMin(firstQueue, secondQueue);
        right_node = findMin(firstQueue, secondQueue);

        // Step 4: Create a new node with frequency
        // equal to the sum of the two nodes frequencies.
        // Enqueue this node to second queue.
        top = create_node('0', left_node->frequenc + right_node->frequenc, left_node, right_node);
        enqueue(secondQueue, top);

    }
    return dequeue(secondQueue); //we return the root of the huffman tree
}

/*
// Driver program to test above functions
int main()
{
    Node* tab_nodes[6];
    int arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(arr) / sizeof(arr[0]);

    for(int i = 0;i<size;i++){
        tab_nodes[i] = create_node(arr[i], freq[i], NULL, NULL);
    }

    Node* huffman_tree = create_huffman_tree_FIFO(tab_nodes,size);

    print_tree_prefixe(huffman_tree);
    return 0;
}
*/
