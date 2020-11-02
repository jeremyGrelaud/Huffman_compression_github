#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "optimized.h"

void build_dico(Node* root, FILE* dico, int arr[], int top)
{
    // Assign 0 to left edge and recur
    if(root->left != NULL){
        arr[top] = 0;
        //AFF(top, "top left")
        build_dico(root->left, dico, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if(root->right != NULL){
        arr[top] = 1;
        //AFF(top, "top right")
        build_dico(root->right, dico, arr, top + 1);
    }

    // If this is a leaf node, then it contains one of the input characters, print the character and its code from arr[]
    if ((root->left == NULL) && (root->right == NULL))
    {
        //AFF(top, "top leaf")
        fprintf(dico, "%d:%d:", root->ascii, root->frequenc);
        for(int i=0 ; i<top ; i++){
            fprintf(dico, "%d", arr[i]);
        }
        fputc(' ', dico);
    }
}

void huffman_compression_in_different_file(FILE* text_to_compress, FILE* dico, FILE* compress, int depth_huffman_tree)
{
    char** tabDictionary = (char**)malloc(NUMBER_OF_ASCII * sizeof(char*));
    for(int i=0 ; i<NUMBER_OF_ASCII ; i++){
        tabDictionary[i] = (char*)malloc(depth_huffman_tree * sizeof(char));
    }

    int alpha = 0;
    do{
        int a; // ascii
        char b[20]; // huffman code
        int c; // frequency
        alpha = fscanf(dico, "%d:%d:%s ", &a, &c, b);

        if(alpha != -1){
            strcpy(tabDictionary[a], b);
            printf("tab = %s et alpha = %d \n", tabDictionary[a], alpha);
        }

    }while(alpha != -1);

    char actualCharacter;
    //fputc('\n', dico); // for the version where the dictionary is just before the compress text
    do{
        actualCharacter = fgetc(text_to_compress);
        if(actualCharacter != EOF){
            fprintf(compress, "%s", tabDictionary[actualCharacter]);
            //fprintf(dico, "%s", tabDictionary[actualCharacter]);// for the version where the dictionary is just before the compress text
        }

    }while(actualCharacter != EOF);

    for(int i=0 ; i<NUMBER_OF_ASCII ; i++) { free(tabDictionary[i]); } free(tabDictionary); // free

}

void huffman_compression_in_same_file(FILE* text_to_compress, FILE* compress, int depth_huffman_tree)
{
    char** tabDictionary = (char**)malloc(NUMBER_OF_ASCII * sizeof(char*));
    for(int i=0 ; i<NUMBER_OF_ASCII ; i++){
        tabDictionary[i] = (char*)malloc(depth_huffman_tree * sizeof(char));
    }

    int alpha = 0;
    do{
        int a; // ascii
        char b[20]; // huffman code
        int c; // frequency
        alpha = fscanf(compress, "%d:%d:%s ", &a, &c, b);

        if(alpha != -1){
            strcpy(tabDictionary[a], b);
            printf("tab = %s et alpha = %d \n", tabDictionary[a], alpha);
        }

    }while(alpha != -1);

    char actualCharacter;
    fputc('\n', compress); // for the version where the dictionary is just before the compress text
    do{
        actualCharacter = fgetc(text_to_compress);
        if(actualCharacter != EOF){
            fprintf(compress, "%s", tabDictionary[actualCharacter]);// for the version where the dictionary is just before the compress text
        }

    }while(actualCharacter != EOF);

    for(int i=0 ; i<NUMBER_OF_ASCII ; i++) { free(tabDictionary[i]); } free(tabDictionary); // free

}

Node* create_node(int ascii, int frequency)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->ascii = ascii;
    new_node->frequenc = frequency;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

Node* create_huffman_tree_by_dicodicodi(FILE* dico)
{
    //Create the root
    Node* tree = create_node(0,0);
    Node* root = (Node*)malloc(sizeof(Node));
    root = tree;

    int alpha = 0;
    do{
        int ascii;
        int frequency;
        char code[20];
        alpha = fscanf(dico, "%d:%d:%s ", &ascii, &frequency, code);
        //printf("ascci = %d ; frq = %d ; code = %s\n", ascii, frequency, code);

        int i = 0;
        while(code[i] != '\0')
        {
            if(code[i] == '0')
            {
                if(tree->left == NULL){
                    tree->left = create_node(0,0);
                }
                tree = tree->left;
            }

            else if(code[i]=='1')
            {
                if(tree->right == NULL){
                    tree->right = create_node(0,0);
                }
                tree = tree->right;
            }
            i++;
        }

        tree->ascii = ascii;
        tree->frequenc = frequency;

        tree = root; // return to the root of the tree

    }while(alpha != -1);

    return tree;
}


void decompression(Node* tree, FILE* compress, FILE* decompress)
{
    int actual;
    Node* root = tree;
    do{
        if(tree->left == NULL && tree->right == NULL) // it is a motherf*cker leaf !!
        {
            fprintf(decompress, "%c", tree->ascii);
            tree = root;
        }
        actual = fgetc(compress);

        if(actual != EOF)
        {
            if(actual == 48){ // 48 = 0
                tree = tree->left;
            }
            else if(actual == 49){ // 49 = 1
                tree = tree->right;
            }
        }

    }while(actual != EOF);

}
