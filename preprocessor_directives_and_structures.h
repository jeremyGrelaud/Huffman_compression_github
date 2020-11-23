#ifndef PREPROCESSOR_DIRECTIVES_AND_STRUCTURES_H_INCLUDED
#define PREPROCESSOR_DIRECTIVES_AND_STRUCTURES_H_INCLUDED


/// Debug
#define AFF(variable, Nom_de_la_Variable) printf("%s = %d\n", Nom_de_la_Variable, variable);
#define RTR printf("\n\n");
#define AFFTAB(Tab, Taille)  for(int i=0 ; i<Taille ; i++){ \
                                printf("%d : %d\n",i, Tab[i]); } \
                            printf("\n");


#define OPEN(fichier, NOM_FICHIER, TYPE_DOUV)   fichier = fopen(NOM_FICHIER, TYPE_DOUV); \
                                                if(fichier == NULL) { exit(0); }


/// Paths to Files
#define Alice "Files/alice.txt"
#define Texte_test "Files/texte_test.txt"

/// Constants
#define NUMBER_OF_ASCII 256

/// Structures

typedef struct Node{
    int ascii;
    int frequenc;
    struct Node *left;
    struct Node *right;
}Node;

typedef struct Element{
    Node* data;
    struct Element *next;
}Element;


#endif // PREPROCESSOR_DIRECTIVES_AND_STRUCTURES_H_INCLUDED
