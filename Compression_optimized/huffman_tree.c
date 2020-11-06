#include <stdio.h>
#include <stdlib.h>

#include "huffman_tree.h"


int number_of_caracters(FILE* fichier)
{
    rewind(fichier); // rewinds the file in case of previous reading
    int compteur = 0;
    while(fgetc(fichier) != EOF) { compteur++; }
    rewind(fichier); // rewinds the file in case of next reading
    return compteur;
}

void trees_free_tree(Node* tree)
{

    if(tree!=NULL){
        trees_free_tree(tree->left);
        trees_free_tree(tree->right);
        free(tree); //ici pour post-fixe
    }
}

/*
void permut(Node** x, Node** y)
{
    Node* temp = *x;
    *x = *y;
    *y = temp;
}

void list_bubble_sort(Node** tab, int taille)
{
    //method with values permutation
    for(int i=0 ; i<taille-1 ; i++)
    {
        for(int j=0 ; j<taille-i-1 ; j++)
        {
            //increasing
            if(tab[j]->frequenc > tab[j+1]->frequenc){
                permut(&tab[j],&tab[j+1]);
            }
        }
    }
}*/

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
    /*int nbCharacter = 0;
    for(int i=0 ; i<NUMBER_OF_ASCII ; i++){
        if(tabFrequencies[i] > 0) { nbCharacter++; }
    }*/ /// Très probablement inutile


    Element* new_elem = NULL;
    Element* theNext = NULL;

    for(int i=NUMBER_OF_ASCII-1 ; i>=0 ; i--)
    {
        if(tabFrequencies[i] > 0)
        {
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->ascii = i;
            new_node->frequenc = tabFrequencies[i];
            new_node->left = NULL;
            new_node->right = NULL;

            new_elem = (Element*)malloc(sizeof(Element));
            new_elem->data = new_node;
            new_elem->next = theNext;
            theNext = new_elem;
        }
    }


    #ifdef DEBUG
    for(int i =0;i<nbCharacter;i++){
        printf("%d : %c -> %d\n",i, (allNode[i])->ascii, (allNode[i])->frequenc);
    }
    printf("\n");
    #endif // Debug

    bubbleSort(new_elem);

    #ifdef DEBUG
    for(int i =0;i<nbCharacter;i++){
        printf("%d : %c -> %d\n",i, (allNode[i])->ascii, (allNode[i])->frequenc);
    }
    printf("\n");
    printList(LSC);
    #endif // DEBUG

    Node* huffman_tree = (Node*)malloc(sizeof(Node));
    huffman_tree = create_huffman_tree_from_LSC(new_elem);

    return huffman_tree;
}

void print_tree_prefixe(Node* tree)
{
    if(tree != NULL)
    {
        printf("%c -> ", tree->ascii);
        print_tree_prefixe(tree->left);
        print_tree_prefixe(tree->right);
    }
}

///fonctions de tri LSC


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

/* Bubble sort the given linked list */
void bubbleSort(Element* start)
{
    
    Element *ptr1;
    Element *ptr2 = NULL;

    /* Checking for empty list */
    if (start != NULL){
        int swapped;
        do
        {
            swapped = 0;
            ptr1 = start;

            while (ptr1->next != ptr2)
            {
                if (ptr1->data->frequenc > ptr1->next->data->frequenc)
                {
                    swape(ptr1, ptr1->next); // a swap of 2 elements in the linked list
                    swapped = 1;
                }
                ptr1 = ptr1->next;
            }
            ptr2 = ptr1;
        }
        while(swapped==1); //we continue while we're still swapping
    }
}

void swape(Element* a, Element* b)
{
    Node* temp = a->data;
    a->data = b->data;
    b->data = temp;
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
        //free(temp);
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
        new_elem->data = (Node*)malloc(sizeof(Node));
        new_elem->next = head; //on le met en tete de liste puis on va retrier
        new_elem->data->left = temp1->data;
        new_elem->data->right = temp2->data;
        new_elem->data->frequenc = temp1->data->frequenc + temp2->data->frequenc;
        new_elem->data->ascii = NULL;


        head = new_elem; //la nouvelle tete de liste
        //mtn il faut retrier la liste
        bubbleSort(head);

    }while(head->next!=NULL);//tant que la liste contient 2 elements ou plus

    return head->data; //contient un Node* qui est la racine de l'arbre créer
}

int depth(Node* tree)
{
    if(tree == NULL){ //on considere qu'il a une profondeur de 0
        return 0;
    }
    else{
        int left_depth = depth(tree->left);
        int right_depth = depth(tree->right);
        if(left_depth > right_depth){
            return 1 + left_depth;
        }
        else{ //pcq dans le cas egal c pareil que l on prenne gauche ou droite
            return 1 + right_depth;
        }
    }
} //attention dans son prog un abrre null a quand meme une profondeur de 1
//il a defini la profondeur comme le nbr de niveaux

