#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman_compression_with_tab.h"


Node* create_node(int ascii, int frequency, Node* leftp, Node* rightp)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->ascii = ascii;
    new_node->frequenc = frequency;
    new_node->left = leftp;
    new_node->right = rightp;

    return new_node;
}


void free_tree(Node* tree)
{
    if(tree != NULL)
    {
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree);
    }
}


int* frequencies(FILE* fichier)
{
    int* tabFrenquencies = (int*)malloc(NUMBER_OF_ASCII * sizeof(int));
    for(int i=0 ; i<NUMBER_OF_ASCII ; i++){
        tabFrenquencies[i] = 0;
    }

    int actualCharact = 0;
    do{
        actualCharact = fgetc(fichier); // we read the character

        if(actualCharact != EOF){
            tabFrenquencies[actualCharact] ++;
        }
    }while (actualCharact != EOF);

    return tabFrenquencies;
}


Node* build_huffman_tree(int* tabFrequencies)
{
    Element* new_elem = NULL;
    Element* theNext = NULL;

    for(int i=NUMBER_OF_ASCII-1 ; i>=0 ; i--)
    {
        if(tabFrequencies[i] > 0)
        {
            Node* new_node = create_node(i, tabFrequencies[i], NULL, NULL);

            new_elem = (Element*)malloc(sizeof(Element));
            new_elem->data = new_node;
            new_elem->next = theNext;
            theNext = new_elem;
        }
    }

    MergeSort(&new_elem);

    Node* huffman_tree = (Node*)malloc(sizeof(Node));
    huffman_tree = create_huffman_tree_from_LSC(new_elem);

    return huffman_tree;
}

/// List functions


void MergeSort(Element** headRef)
{
    Element* head = *headRef;
    Element* a;
    Element* b;

    // Base case -- length 0 or 1
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    // Split head into 'a' and 'b' sublists
    Element* slow = head;
    Element* fast = head->next;

    // Advance fast two element, and advance slow one element
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // slow is before the midpoint in the list, so split it in two at that point.
    a = head;
    b = slow->next;
    slow->next = NULL;

    // Recursively sort the sublists
    MergeSort(&a);
    MergeSort(&b);

    /* merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}

// From https:// www.geeksforgeeks.org/?p=3622
Element* SortedMerge(Element* a, Element* b)
{
    Element* result = NULL;

    // Basics cases
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    // Pick either a or b, and recur
    if (a->data->frequenc <= b->data->frequenc) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}


Element* remove_first_elem(Element** head)
{
    if (*head == NULL){
        return NULL;
    }
    else{
        // Move the head pointer to next
        Element* temp = (*head);
        (*head) = (*head)->next;
        return temp;
    }
}


Node* create_huffman_tree_from_LSC(Element* head)
{
    Element* temp1;
    Element* temp2;

    do{
        temp1 = remove_first_elem(&head);
        //printf("ascii : %c , frequence : %d \n ", temp1->data->ascii, temp1->data->frequenc);
        temp2 = remove_first_elem(&head);
        //printf("ascii : %c , frequence : %d \n ", temp2->data->ascii, temp2->data->frequenc);

        Element* new_elem = (Element*)malloc(sizeof(Element));
        new_elem->data = create_node(0, temp1->data->frequenc + temp2->data->frequenc, temp1->data, temp2->data);
        new_elem->next = head; //it points on the actual head of the list

        head = new_elem; //it becomes the new head
        MergeSort(&head);

    }while(head->next != NULL);//we continue while the list contains 2 elements or more

    return head->data; //contains a Node* wich is the root of the huffman tree we create
}

/// Compression functions


int depth(Node* tree)
{
    if(tree == NULL){ //we consider a depth of 0
        return 0;
    }
    else{
        int left_depth = depth(tree->left);
        int right_depth = depth(tree->right);
        if(left_depth > right_depth){
            return 1 + left_depth;
        }
        else{ //in this case it's the same if we take left or right
            return 1 + right_depth;
        }
    }
}


void build_dico(Node* tree, char** tabDictionary, unsigned char arr[], int top)
{
    // Assign 0 to left edge and recur
    if(tree->left != NULL){
        arr[top] = '0';
        build_dico(tree->left, tabDictionary, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if(tree->right != NULL){
        arr[top] = '1';
        build_dico(tree->right, tabDictionary, arr, top + 1);
    }

    // If this is a leaf node, then it contains one of the input characters, print the character and its code from arr[]
    if ((tree->left == NULL) && (tree->right == NULL))
    {
        arr[top] = '\0';
        tabDictionary[tree->ascii] = (char*)malloc((top+1) * sizeof(char));
        strcpy(tabDictionary[tree->ascii], (const char*)arr);
        //printf("%c, %s\n", tree->ascii, tabDictionary[tree->ascii]);
    }
}


void huffman_compression_in_same_file_with_xfactor(FILE* text_to_compress, FILE* compress, char** tabDictionary)
{
    for(int i=0 ; i<NUMBER_OF_ASCII ; i++)
    {
        if(tabDictionary[i] != NULL){
            fprintf(compress, " %d:%s", i, tabDictionary[i]);
        }
    }

    fputc('\n', compress);

    int actualCharacter = 0, precedentCharacter = 0, sameCharacter = 1;
    do{
        actualCharacter = fgetc(text_to_compress);

        if((sameCharacter != 1)&&(actualCharacter != precedentCharacter))
        {
            fprintf(compress, "x%d ", sameCharacter);
            sameCharacter = 1;
        }

        if(actualCharacter != EOF)
        {
            if(actualCharacter == precedentCharacter){
                sameCharacter++;
            }
            else{
                fprintf(compress, "%s", tabDictionary[actualCharacter]);
            }
        }
        precedentCharacter = actualCharacter;

    }while(actualCharacter != EOF);

}


Node* create_huffman_tree_from_dictionary(FILE* compress)
{
    //Create the root
    Node* tree = create_node(0, 0, NULL, NULL);
    Node* root = (Node*)malloc(sizeof(Node));
    root = tree;

    int alpha = 0;
    do{
        alpha = fgetc(compress);

        if(alpha != '\n')
        {
            int ascii;
            char code[50];
            fscanf(compress, "%d:%50s", &ascii, code);
            //printf("ascci = %d ; code = %s", ascii, code);

            int i = 0;
            while(code[i] != '\0')
            {
                if(code[i] == '0')
                {
                    if(tree->left == NULL){
                        tree->left = create_node(0, 0, NULL, NULL);
                    }
                    tree = tree->left;
                }

                else if(code[i]=='1')
                {
                    if(tree->right == NULL){
                        tree->right = create_node(0, 0, NULL, NULL);
                    }
                    tree = tree->right;
                }
                i++;
            }

            tree->ascii = ascii;
            tree->frequenc = 0;

            tree = root; // return to the root of the tree
        }

    }while(alpha != '\n');
    
    free(root);
    return tree;
}


void huffman_decompression_with_xfactor(Node* tree, FILE* compress, FILE* decompress)
{
    int actual;
    int precedent;
    Node* root = tree;
    do{
        if(tree->left == NULL && tree->right == NULL) // it is a motherf*cker leaf !!
        {
            fprintf(decompress, "%c", tree->ascii);
            precedent = tree->ascii;
            tree = root;
        }

        actual = fgetc(compress);

        if(actual != EOF)
        {
            if(actual == 'x')
            {
                fscanf(compress, "%d ", &actual);
                for(int i=1 ; i<actual ; i++){
                    fprintf(decompress, "%c", precedent);
                }
                precedent = 0;
            }

            else if(actual == '0'){
                tree = tree->left;
            }
            else if(actual == '1'){
                tree = tree->right;
            }
        }

    }while(actual != EOF);

}

/// Print


void print_tree_prefixe(Node* tree)
{
    if(tree != NULL)
    {
        printf("%d:%c -> ", tree->frequenc, tree->ascii);
        print_tree_prefixe(tree->left);
        print_tree_prefixe(tree->right);
    }
}


void printList(Element* debut)
{
    Element *temp = debut;
    printf("\n");
    while (temp!=NULL)
    {
        printf("ascii : %c , frequence : %d \n ", temp->data->ascii, temp->data->frequenc);
        temp = temp->next;
    }
}

/// Final functions


void compression(FILE* text_to_convert, FILE* compress, char* texte_path, char* compress_path)
{
    printf("Compression ... \t");
    OPEN(text_to_convert, texte_path, "r")

    int* tab = NULL;
    tab = frequencies(text_to_convert);

    Node* huffman_tree = build_huffman_tree(tab);

    free(tab);
    rewind(text_to_convert);
    //print_tree_prefixe(huffman_tree);
    //AFF(depth_huffman_tree, "depth_huffman_tree")

    OPEN(compress, compress_path, "w+")

    int depth_huffman_tree = depth(huffman_tree);
    unsigned char* arr = (unsigned char*)malloc(depth_huffman_tree * sizeof(unsigned char));

    char** tabDictionary = NULL;
    tabDictionary = (char**)malloc(NUMBER_OF_ASCII * sizeof(char*));
    for(int i = 0 ; i<NUMBER_OF_ASCII ; i++){
        tabDictionary[i] = NULL;
    }

    build_dico(huffman_tree, tabDictionary, arr, 0);

    free(arr);
    rewind(compress);

    huffman_compression_in_same_file_with_xfactor(text_to_convert, compress, tabDictionary);

    //freeing
    for(int i=0 ; i<NUMBER_OF_ASCII ; i++) { free(tabDictionary[i]); } free(tabDictionary);

    free_tree(huffman_tree);
    fclose(text_to_convert);
    fclose(compress);

    printf("Compression achieve ^_^ That was fast ! \n");
}


void decompression(FILE* compress, FILE* decompress, char* compress_path, char* decompress_path)
{
    printf("Decompression ...\t");

    OPEN(compress, compress_path, "r")

    Node* new_huffman_tree = NULL;
    new_huffman_tree = create_huffman_tree_from_dictionary(compress);
    //print_tree_prefixe(new_huffman_tree);

    OPEN(decompress, decompress_path, "w")
    huffman_decompression_with_xfactor(new_huffman_tree, compress, decompress);

    free_tree(new_huffman_tree);
    fclose(compress);
    fclose(decompress);

    printf("Decompression achieve 0_0 \n");
}
