#ifndef HUFFMAN_COMPRESSION_WITH_TAB_H_INCLUDED
#define HUFFMAN_COMPRESSION_WITH_TAB_H_INCLUDED

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
#define Compress "Files/compress.txt"
#define Decompress "Files/decompress.txt"
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

/// Functions

Node* create_node(int ascii, int frequency, Node* leftp, Node* rightp);
void free_tree(Node* tree);

int* frequencies(FILE* fichier);
Node* build_huffman_tree(int* tabFrequencies);

void bubbleSort(Element* start);
void swape(Element* a, Element* b);
Element* remove_first_elem(Element** head);
Node* create_huffman_tree_from_LSC(Element* head);

int depth(Node* tree);

void build_dico(Node* tree, char** tabDictionary, unsigned char arr[], int top);
void huffman_compression_in_same_file_with_xfactor(FILE* text_to_compress, FILE* compress, char** tabDictionary);
Node* create_huffman_tree_from_dictionary(FILE* compress);
void huffman_decompression_with_xfactor(Node* tree, FILE* compress, FILE* decompress);

void print_tree_prefixe(Node* tree);
void printList(Element* debut);

void compression(FILE* text_to_convert, FILE* compress, char* texte_path, char* compress_path);
void decompression(FILE* compress, FILE* decompress, char* compress_path, char* decompress_path);

#endif // HUFFMAN_COMPRESSION_WITH_TAB_H_INCLUDED
