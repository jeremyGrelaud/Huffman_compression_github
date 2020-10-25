// Huffman_compression_github.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>

#include "preprocessor_directives_and_structures.h"

#include "Compression_non_optimized/non_optimized.h"

#include "Compression_optimized/huffman_tree.h"
#include "Compression_optimized/optimized.h"


typedef struct el_dico{
    int lettre;
    char* code;
}el_dico;


Node* build_huffman_tree(int* tabFrequencies)
{
    int nbCaracter = 0;
    for(int i=0 ; i<255 ; i++){
        if(tabFrequencies[i] > 0) { nbCaracter++; }
    }

    AFF(nbCaracter, "nbCaracter")

    Node** allNode = (Node**)malloc(nbCaracter * sizeof(Node*));
    int compteur = 0;

    for(int i=0 ; i<255 ; i++)
    {
        if(tabFrequencies[i] > 0)
        {
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->ascii = i;
            new_node->frequenc = tabFrequencies[i];
            new_node->left = NULL;
            new_node->right = NULL;

            allNode[compteur] = new_node;
            compteur++;
        }
    }

    for(int i =0 ; i<nbCaracter ; i++){
        printf("%d : %c -> %d\n",i, (allNode[i])->ascii, (allNode[i])->frequenc);
    }
    printf("\n");

    list_bubble_sort(allNode, nbCaracter);

    for(int i =0;i<nbCaracter;i++){
        printf("%d : %c -> %d\n",i, (allNode[i])->ascii, (allNode[i])->frequenc);
    }
    printf("\n");


    Node* tree = (Node*)malloc(sizeof(Node));
    tree = create_huffman_tree(allNode, nbCaracter-1);

    return tree;

}

void build_dico(Node* tree, FILE* fichier)
{
    printf("ok");
    if(tree != NULL)
    {
        AFF(tree->ascii, "tree->ascii")
        fprintf(fichier, "%c : \n", tree->ascii);

        build_dico(tree->left, fichier);
        build_dico(tree->right, fichier);
    }
    else{
        printf("null");
    }

}


int main()
{

    OPEN(texte, Alice, "r")
    OPEN(texte_binary, Binary, "w")

    convert_file_in_binary(texte, texte_binary);

    fclose(texte);
    fclose(texte_binary);

    OPEN(texte_binary2, Binary, "r")
    OPEN(texte_convert, Convert, "w")

    convert_binary_in_file(texte_binary2, texte_convert);

    fclose(texte_convert);
    fclose(texte_binary2);






    OPEN(texte2, Alice, "r")
    int* tab = NULL;
    tab = frequencies(texte2);

    Node* huffman_tree = (Node*)malloc(sizeof(Node));
    huffman_tree = build_huffman_tree(tab);

    print_tree_prefixe(huffman_tree);

    fclose(texte2);

    OPEN(dico, Dictionary, "w")
    build_dico(huffman_tree, dico);


    fclose(dico);


    return 0;
}


// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
