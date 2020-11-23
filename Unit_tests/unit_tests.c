#include <stdio.h>
#include <stdlib.h>

#include "unit_tests.h"

int number_of_caracters(FILE* fichier)
{
    rewind(fichier); // rewinds the file in case of previous reading
    int compteur = 0;
    while(fgetc(fichier) != EOF) { compteur++; }
    rewind(fichier); // rewinds the file in case of next reading
    return compteur;
}

int TU_convert_10_to_base_octet()
{
    char* test = (char*) malloc(sizeof(char)*8);
    char res2[8] = "00000010";
    char res3[8] = "00000011";
    char res4[8] = "00000100";
    char res5[8] = "00000101";
    char* res[4];
    res[0] = res2;
    res[1] = res3;
    res[2] = res4;
    res[3] = res5;
    int indice_res=0;
    for (int i = 2; i<=5; i++)
    {
        //convert_10_to_base_octet(i, 2, test);
        printf("%d en base 2 donne d'apres notre fonction : ", i);
        for(int j = 0; j<8; j++)
        {
            printf("%d", test[j]);
        }
        printf("\n");
        printf("Le bon resultat est : ");
        for(int j = 0; j<8; j++)
        {
            printf("%c", res[indice_res][j]);
        }
        printf("\n");
        for(int j = 0; j<8; j++)
        {
            if(res[indice_res][j]-48 != test[j])
            {
                printf(" %d %d ",res[indice_res][j], test[j]);
                free(test);
                return 0;
            }
        }
        indice_res++;
    }
    free(test);
    printf("Cette fonction marche \n");
    return 1;
}

int compare(Node* tree1, Node* tree2)
{
    if(tree1 == NULL && tree2 == NULL)
    {
        return 1;
    }
    else if(tree1 == NULL || tree2 == NULL)
    {
        return 0;
    }
    else
    {

        if(tree1->ascii != tree2->ascii || tree1->frequenc != tree2->frequenc)
        {
            return ( 0 ); //&& compare(tree1->left, tree2->left) && compare(tree1->right, tree2->right) );
        }
        else
        {
            return ( compare(tree1->left, tree2->left) && compare(tree1->right, tree2->right) );
        }

    }

}

int TU_create_huffman_tree_from_LSC()
{
    Element* el1 = (Element*)malloc(sizeof(Element));
    Element* el2 = (Element*)malloc(sizeof(Element));
    Element* el3 = (Element*)malloc(sizeof(Element));
    Element* el4 = (Element*)malloc(sizeof(Element));
    el1->data = create_node('A', 1, NULL, NULL);
    el1->next = el2;
    el2->data = create_node('E', 1, NULL, NULL);
    el2->next = el3;
    el3->data = create_node('T', 1, NULL, NULL);
    el3->next = el4;
    el4->data = create_node('S', 3, NULL, NULL);
    el4->next = NULL;

    printList(el1);
    RTR

    Node* huff_tree = create_huffman_tree_from_LSC(el1);
    printf("huff_tree :");
    print_tree_prefixe(huff_tree);
    RTR

    Node* true_tree = NULL;
    Node* node1 = NULL;
    Node* node2 = NULL;
    Node* node3 = NULL;
    Node* node4 = NULL;
    Node* node5 = NULL;
    Node* node6 = NULL;
    node6 = create_node('E', 1, NULL, NULL);
    node5 = create_node('A', 1, NULL, NULL);
    node4 = create_node(0, 2, node5, node6);
    node3 = create_node('T', 1, NULL, NULL);
    node1 = create_node(0, 3, node3, node4);
    node2 = create_node('S', 3, NULL, NULL);
    true_tree = create_node(0, 6, node1, node2);


    printf("true_tree : ");
    print_tree_prefixe(true_tree);
    RTR

    int a=compare(true_tree, huff_tree);
    //printf("a : %d", a);

    return a;
}

int TU_frequencies()
{
    FILE* tasse = NULL;
    OPEN(tasse,Texte_test,"r")
    int* tabfreq = frequencies(tasse);
    fclose(tasse);
    int* true_tab = calloc(NUMBER_OF_ASCII, sizeof(int));
    true_tab[65]=1;
    true_tab[69]=1;
    true_tab[83]=3;
    true_tab[84]=1;

    for(int i = 0; i<NUMBER_OF_ASCII; i++)
    {
        //printf("%d:%d  ", true_tab[i], tabfreq[i]);
        if(tabfreq[i] != true_tab[i])
        {
            return 0;
        }
    }
    return 1;
}

int TU_decompression(Node* new_huffman_tree, FILE* compress, FILE* decompress, FILE* original_file)
{
    huffman_decompression_with_xfactor(new_huffman_tree, compress, decompress);
    int char_original;
    int char_decomp;
    do {
        char_original = fgetc(original_file);
        char_decomp = fgetc(decompress);
        if(char_original != char_decomp)   // One character is different :-/
        {
            return 0;
        }
    }while(char_original != EOF || char_decomp != EOF);
    if(char_decomp != EOF || char_original != EOF)  // Original and decompress do not have the same size :-/
    {
        return 0;
    }
    return 1;
}

int TU_build_dico()
{
    Node* true_tree = NULL;
    Node* node1 = NULL;
    Node* node2 = NULL;
    Node* node3 = NULL;
    Node* node4 = NULL;
    Node* node5 = NULL;
    Node* node6 = NULL;
    node6 = create_node('E', 1, NULL, NULL);
    node5 = create_node('A', 1, NULL, NULL);
    node4 = create_node(0, 2, node5, node6);
    node3 = create_node('T', 1, NULL, NULL);
    node1 = create_node(0, 3, node3, node4);
    node2 = create_node('S', 3, NULL, NULL);
    true_tree = create_node(0, 6, node1, node2);

    unsigned char* arr = (unsigned char*)malloc(4 * sizeof(unsigned char));

    char** tab_dico_true = NULL;
    tab_dico_true = (char**)malloc(NUMBER_OF_ASCII * sizeof(char*));
    char** tab_dico_test = NULL;
    tab_dico_test = (char**)malloc(NUMBER_OF_ASCII * sizeof(char*));

    for(int i = 0 ; i<NUMBER_OF_ASCII ; i++){
        tab_dico_true[i] = NULL;
        tab_dico_test[i] = NULL;
    }


    tab_dico_true[65] = (char*)malloc((3+1) * sizeof(char));
    tab_dico_true[65] ="010";

    tab_dico_true[69] = (char*)malloc((3+1) * sizeof(char));
    tab_dico_true[69] ="011";

    tab_dico_true[83] = (char*)malloc((1+1) * sizeof(char));
    tab_dico_true[83] ="1";

    tab_dico_true[84] = (char*)malloc((2+1) * sizeof(char));
    tab_dico_true[84] ="00";

    build_dico(true_tree, tab_dico_test, arr, 0);

    for(int i = 0; i<NUMBER_OF_ASCII; i++)
    {
        if(tab_dico_true[i] == NULL){
            if(tab_dico_test[i] != NULL){
                return 0;
            }
        }

        if(tab_dico_test[i] == NULL){
            if(tab_dico_true[i] != NULL){
                return 0;
            }
        }

        else{
            //printf("%d -> tab_dico_test : %s - %s : tab_dico_true\n",i, tab_dico_test[i], tab_dico_true[i]);
            if(strcmp(tab_dico_test[i], tab_dico_true[i]) != 0){
                return 0;
            }
        }
    }
    return 1;
}

int For_rule_them_all(int number_of_test)
{
    int sum = 0;
    //sum += TU_convert_10_to_base_octet();
    sum += TU_frequencies();
    sum += TU_create_huffman_tree_from_LSC();
    sum += TU_build_dico();

    if (sum == number_of_test)
    {
        printf("Everything works.");
        return 1;
    }
    else
    {
        printf("Try next time, Ashen One !");
        return 0;
    }
}

void Test(FILE* text_to_convert, FILE* compress, FILE* decompress, FILE* non_compress, char* texte_path, char* compress_path, char* decompress_path, char* non_compress_path)
{
    OPEN(text_to_convert, texte_path, "r")
    OPEN(compress, compress_path, "r")
    OPEN(non_compress, non_compress_path, "r")
    OPEN(decompress, decompress_path, "r")
    float a = number_of_caracters(text_to_convert);
    float b = number_of_caracters(compress);
    float c = number_of_caracters(non_compress);
    float d = number_of_caracters(decompress);
    RTR
    printf("\t--- Number of characters ---\n");
    printf("Text to convert = %.0f ; Compress = %.0f ; Non_compress = %.0f ; Decompress = %.0f \n", a, b, c, d);
    printf("Compression rate = %.2f (the smaller, the better)\n", (b*100)/c);
    printf("Loss = %.0f (must be 0, otherwise problem)", a-d);
    RTR
    fclose(text_to_convert);
    fclose(compress);
    fclose(non_compress);
    fclose(decompress);
}

void Test_without_non_compress(FILE* text_to_convert, FILE* compress, FILE* decompress, char* texte_path, char* compress_path, char* decompress_path)
{
    OPEN(text_to_convert, texte_path, "r")
    OPEN(compress, compress_path, "r")
    OPEN(decompress, decompress_path, "r")
    float a = number_of_caracters(text_to_convert);
    float b = number_of_caracters(compress);
    float d = number_of_caracters(decompress);
    RTR
    printf("\t--- Number of characters ---\n");
    printf("Text to convert = %.0f ; Compress = %.0f ; Decompress = %.0f \n", a, b, d);
    printf("Compression rate = Impossible to calculate\n");
    printf("Loss = %.0f (must be 0, otherwise problem)", a-d);
    RTR
    fclose(text_to_convert);
    fclose(compress);
    fclose(decompress);
}
