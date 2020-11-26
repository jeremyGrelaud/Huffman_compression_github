#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman_compression_with_avl_and_fifo.h"
#include "huffman_compression_with_tab.h"

/**
 * @brief Create a queue object
 * 
 * @return Queue* 
 */
Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data_queue = NULL;
    return q;
}

/**
 * @brief Check if a queue is empty or not
 * 
 * @param q The queue
 * @return int A booléen
 */
int is_empty(Queue* q) {
    if (q->data_queue == NULL) {
        return 1; //there queue is empty
    }
    else {
        return 0;
    }
}

/**
 * @brief Check if the queue is at minimum size 1
 * 
 * @param q The queue
 * @return int A booléen
 */
int isSizeOne(Queue* q) {
    if ((q->data_queue != NULL) && (q->data_queue->next == NULL)) {
        return 1;
    }
    else {
        return 0;
    }
}

/**
 * @brief Add a node at the end of the queue
 * 
 * @param q The queue
 * @param new_node The node added
 */
void enqueue(Queue* q, Node* new_node) {
    //add at the end
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

/**
 * @brief Remove a node at the beginning
 * 
 * @param q The queue
 * @return Node* The node deleted
 */
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


/**
 * @brief Get the node with the lowest frequency from two queues //
 * 
 * @param firstQueue The first queue
 * @param secondQueue The second queue
 * @return Node* The node with the lowest frequency
 */
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

/**
 * @brief Create a huffman tree from atab of node
 * 
 * @param tab Tab of node
 * @param size_tab The size of the tab
 * @return Node* The root
 */
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
        top = create_node(0, left_node->frequenc + right_node->frequenc, left_node, right_node);

        enqueue(secondQueue, top);

    }
    return dequeue(secondQueue); //we return the root of the huffman tree
}


/**
 * @brief Create a node avl object
 *
 * @param ascii The code ascii of the character
 * @param huffman_code The huffman code
 * @return Node_AVL* A node of the AVL
 */
Node_AVL* create_node_avl(int ascii, char* huffman_code,int taille)
{
    Node_AVL* new_node = (Node_AVL*)malloc(sizeof(Node_AVL));
    new_node->charac = ascii;

    //char str[taille];
    char* str = (char*)malloc(taille * sizeof(char));
    int index = 0;
    for (int i=0; i<taille; i++)
        index += sprintf(&str[index], "%d", huffman_code[i]);
        //index += snprintf(&str[index],taille, "%d", huffman_code[i]);

    new_node->huffman_code = (char*)malloc(taille * sizeof(char));
    //new_node->huffman_code = str;
    strcpy(new_node->huffman_code,str);

    //printf("%s\n",new_node->huffman_code);
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

/**
 * @brief Add a node to a search binary tree
 * 
 * @param tree The binary search tree
 * @param new_node The new node
 */
void add_node_bst(Node_AVL** tree, Node_AVL* new_node){
    if(*tree == NULL){
        *tree = new_node;
    }
    else if ((*tree)->charac < new_node->charac){ //else there's 2 cases
        add_node_bst(&((*tree)->right),new_node); //right
    }
    else if ((*tree)->charac > new_node->charac){ //left
        add_node_bst(&((*tree)->left),new_node);
    }
}

/**
 * @brief Add a node to an AVL
 * 
 * @param tree The AVL
 * @param new_node The new node
 */
void add_node_avl(Node_AVL** tree, Node_AVL* new_node){
    add_node_bst(tree, new_node);
    trees_balance_BST(tree);
}

/**
 * @brief Count the depth of an AVL
 * 
 * @param tree The AVL
 * @return int The depth
 */
int depth_AVL(Node_AVL* tree){
    if(tree == NULL){
        return 0;
    }
    else{
        int left_depth = depth_AVL(tree->left);
        int right_depth = depth_AVL(tree->right);
        if(left_depth > right_depth){
            return 1 + left_depth;
        }
        else{
            return 1 + right_depth;
        }
    }
}

/**
 * @brief Give the balance factor of an AVL
 * 
 * @param tree The AVL
 * @return int The balance factor
 */
int balance_factor(Node_AVL* tree){
    if(tree == NULL){
        return 0;
    }
    else{
        return depth_AVL(tree->right) - depth_AVL(tree->left);
    }
}

///right rotation
void r_rot(Node_AVL** tree){
    if((*tree)!= NULL){
        Node_AVL* temp = (*tree)->left;
        (*tree)->left = temp->right;
        temp->right = (*tree);
        *tree = temp;
    }
}
///left rotation
void l_rot(Node_AVL** tree){
    if((*tree)!= NULL){
        Node_AVL* temp = (*tree)->right;
        (*tree)->right = temp->left;
        temp->left = (*tree);
        *tree = temp;
    }
}

/**
 * @brief Balance an AVL via the balance factor
 * 
 * @param tree The AVL
 */
void trees_balance_BST(Node_AVL** tree){

    if((*tree)!= NULL){ //we start from the bottom to balance the deepest nodes it correspond to post-fix traversal
        trees_balance_BST(&((*tree)->left));
        trees_balance_BST(&((*tree)->right));

        int bfact = balance_factor(*tree);
        if(bfact <= -2){ //left case
            if(balance_factor((*tree)->left)>0){ //left right
                l_rot(&((*tree)->left)); //we make a left rotation on the sub left tree
            }
            r_rot(tree); //right rotation on ourselves
        }
        else if(bfact >= 2){
            if(balance_factor((*tree)->right)<0){
                r_rot(&((*tree)->right));
            }
            l_rot(tree);
        }
    }
}

/**
 * @brief Build a dico and an AVL via a huffman tree
 * 
 * @param huffman_tree The huffman tree
 * @param avl_tree The AVL we gonna build
 * @param compress The dictionary we gonna build (empty file)
 * @param arr The tab of each character 
 * @param top The size we increment
 */
void build_dico_and_avl(Node* huffman_tree, Node_AVL** avl_tree, FILE* compress, char arr[], int top)
{
    // Assign 0 to left edge and recur
    if(huffman_tree->left != NULL){
        arr[top] = 0;
        build_dico_and_avl(huffman_tree->left, avl_tree, compress, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if(huffman_tree->right != NULL){
        arr[top] = 1;
        build_dico_and_avl(huffman_tree->right, avl_tree, compress, arr, top + 1);
    }

    // If this is a leaf node, then it contains one of the input characters, print the character and its code from arr[]
    if ((huffman_tree->left == NULL) && (huffman_tree->right == NULL))
    {
        add_node_avl(avl_tree, create_node_avl(huffman_tree->ascii, arr, top));

        fprintf(compress, " %d:", huffman_tree->ascii);
        //printf("%d : ", huffman_tree->ascii);
        for(int i=0 ; i<top ; i++){
            //printf("%d ", arr[i]);
            fprintf(compress, "%d", arr[i]);
        }
    }
}
/**
 * @brief Run through the AVL to find the huffman code of the character
 * 
 * @param tree The AVL
 * @param actualCharacter The character
 * @return char* The huffman code
 */
char* traversal_avl(Node_AVL* tree, int actualCharacter)
{
    if(tree != NULL)
    {
        if(tree->charac == actualCharacter){
            return tree->huffman_code;
        }
        else if(tree->charac > actualCharacter){
            return traversal_avl(tree->left, actualCharacter);
        }
        else if(tree->charac < actualCharacter){
            return traversal_avl(tree->right, actualCharacter);
        }
    }
}

/**
 * @brief Compress in the file of the dictionary with the xfactor of the AVL
 * 
 * @param text_to_compress The text we gonna compress
 * @param compress The compressed text
 * @param huffman_avl The AVL create via the huffman tree
 */
void huffman_compression_in_same_file_with_xfactor_avl(FILE* text_to_compress, FILE* compress, Node_AVL* huffman_avl)
{
    fputc('\n', compress); // for the version where the dictionary is just before the compress text

    int actualCharacter, precedentCharacter = 0;
    int sameCharacter = 1;
    do{
        actualCharacter = fgetc(text_to_compress);
        if(actualCharacter != EOF)
        {
            if(actualCharacter == precedentCharacter){
                sameCharacter++;
            }
            else
            {
                if(sameCharacter != 1)
                {
                    fprintf(compress, "x%d ", sameCharacter);
                    sameCharacter = 1;
                }

                fprintf(compress, "%s", traversal_avl(huffman_avl, actualCharacter));

            }
            precedentCharacter = actualCharacter;
        }

    }while(actualCharacter != EOF);
}

/**
 * @brief Free an AVL
 * 
 * @param tree The AVL
 */
void free_tree_avl(Node_AVL* tree)
{
    if(tree != NULL)
    {
        free_tree_avl(tree->left);
        free_tree_avl(tree->right);
        free(tree);
    }
}

/**
 * @brief Print an AVL in the infixe order
 * 
 * @param tree The AVL
 */
void print_tree_infixe_avl(Node_AVL* tree)
{
    if(tree != NULL)
    {

        print_tree_infixe_avl(tree->left);
        printf("%s:%c -> ", tree->huffman_code, tree->charac);
        print_tree_infixe_avl(tree->right);
    }
    else{
        printf("NULL -> ");
    }
}

/**
 * @brief Compress a text to another file
 * 
 * @param text_to_convert The text we gonna compress
 * @param compress The compressed text
 * @param texte_path The path of the file we gonna compress
 * @param compress_path The path of the compressed text
 */
void compression_avl(FILE* text_to_convert, FILE* compress, char* texte_path, char* compress_path)
{
    printf("Compression ... \t");
    OPEN(text_to_convert, texte_path, "r")

    int* tab = NULL;
    tab = frequencies(text_to_convert);

    Node* huffman_tree = build_huffman_tree(tab);

    free(tab);
    rewind(text_to_convert);

    int depth_huffman_tree = depth(huffman_tree);
    //print_tree_prefixe(huffman_tree);
    //AFF(depth_huffman_tree, "depth_huffman_tree")

    OPEN(compress, compress_path, "w+")

    char* arr = (char*)malloc(depth_huffman_tree * sizeof(char));
    Node_AVL* huffman_avl = NULL;
    build_dico_and_avl(huffman_tree, &huffman_avl, compress, arr, 0);
    //print_tree_infixe_avl(huffman_avl);
    free(arr);

    huffman_compression_in_same_file_with_xfactor_avl(text_to_convert, compress, huffman_avl);

    free_tree_avl(huffman_avl);
    free_tree(huffman_tree);
    fclose(text_to_convert);
    fclose(compress);

    printf("Compression achieve ^_^ That was fast ! \n");

}


