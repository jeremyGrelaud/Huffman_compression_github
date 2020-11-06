#include <stdio.h>
#include <stdlib.h>

#include "preprocessor_directives_and_structures.h"

#include "manip_files_non_compress/manip_files_non_compress.h"

#include "Compression_optimized/huffman_tree.h"
#include "Compression_optimized/optimized.h"


void compression(FILE* text_to_convert, FILE* dicodicodi, FILE* compress)
{
    int* tab = NULL;
    tab = frequencies(text_to_convert);

    Node* huffman_tree = (Node*)malloc(sizeof(Node));
    huffman_tree = build_huffman_tree(tab);
    rewind(text_to_convert);

    int depth_huffman_tree = depth(huffman_tree);

    int* arr = (int*)malloc(depth_huffman_tree * sizeof(int));
    build_dico(huffman_tree, dicodicodi, arr, depth_huffman_tree);
    rewind(dicodicodi);
    trees_free_tree(huffman_tree);
    free(huffman_tree);

    huffman_compression_in_different_file(text_to_convert, dicodicodi, compress, 0);

}

/*
int search_element(Node* tree, int val, int arr[], int top)
{
    if(tree != NULL)
    {
        if(tree->ascii == val)
        {
            return 1;
        }
        else{

            arr[top] = 0;
            /*for (int i = 0; i < top; i++){
                printf("%d", arr[i]);
            }
            printf("\n");
            search_element(tree->left, val, arr, top + 1);


            arr[top] = 1;
            /*for (int i = 0; i < top; i++){
                printf("%d", arr[i]);
            }
            printf("\n");
            search_element(tree->right, val, arr, top + 1);
        }

    }
    else
        return NULL;
}

void decompression(FILE* compress, Node* huffman_tree)
{
    int actualCharacter = 0;

    do{
        actualCharacter = fgetc(compress);
        if(actualCharacter != EOF)
        {
            int arr[MAX_TREE_HT], top = 0;
            search_element(huffman_tree, actualCharacter, arr, top);
            for (int i = 0; i < top; i++){
                printf("%d", arr[i]);
            }
            printf("\n");

            //system("pause");
        }

    }while(actualCharacter != EOF);

}*/

int main()
{
    FILE* text_to_convert = NULL;
    FILE* dicodicodi = NULL;
    FILE* compress = NULL;
    FILE* non_compress = NULL;
    FILE* decompress = NULL;

    OPEN(text_to_convert, Entire_Alice, "r")
    OPEN(dicodicodi, Dictionary, "w+")

    int* tab = NULL;
    tab = frequencies(text_to_convert);

    Node* huffman_tree = (Node*)malloc(sizeof(Node));
    huffman_tree = build_huffman_tree(tab);
    free(tab);
    print_tree_prefixe(huffman_tree);

    rewind(text_to_convert);

    RTR

    int depth_huffman_tree = depth(huffman_tree);
    AFF(depth_huffman_tree, "depth_huffman_tree") system("pause");

    int* arr = (int*)malloc(depth_huffman_tree * sizeof(int));
    build_dico(huffman_tree, dicodicodi, arr, 0);
    rewind(dicodicodi);
    trees_free_tree(huffman_tree);
    free(huffman_tree);

    OPEN(compress, Compress, "w+")

    huffman_compression_in_different_file(text_to_convert, dicodicodi, compress, depth_huffman_tree);
    rewind(text_to_convert);
    rewind(dicodicodi);
    rewind(compress);

    OPEN(non_compress, Non_compress, "w")
    convert_file_in_binary(text_to_convert, non_compress);

    OPEN(decompress, Decompress, "w")

    Node* new_huffman_tree = (Node*)malloc(sizeof(Node));
    new_huffman_tree = create_huffman_tree_by_dicodicodi(dicodicodi);
    print_tree_prefixe(new_huffman_tree);

    int actual;
    decompression(new_huffman_tree, compress, decompress);
    trees_free_tree(new_huffman_tree);

    fclose(non_compress);
    fclose(dicodicodi);
    fclose(text_to_convert);
    fclose(compress);
    fclose(decompress);




    /// Test
    OPEN(text_to_convert, Entire_Alice, "r")
    OPEN(compress, Compress, "r")
    OPEN(non_compress, Non_compress, "r")
    OPEN(decompress, Decompress, "r")
    RTR
    float a = number_of_caracters(text_to_convert);
    float b = number_of_caracters(compress);
    float c = number_of_caracters(non_compress);
    float d = number_of_caracters(decompress);
    printf("Alice = %.0f ; Compress = %.0f ; Non_compress = %.0f ; Decompress = %.0f \n", a, b, c, d);
    printf("Pourcentage = %.2f", (b*100)/c);
    printf("\nPerte = %.0f (doit valoir 0, sinon probleme)", a-d);
    RTR
    fclose(text_to_convert);
    fclose(compress);
    fclose(non_compress);
    fclose(decompress);

    return 0;
}


/*
    OPEN(text_to_convert, Alice, "r")
    OPEN(dicodicodi, Dictionary, "w+")
    OPEN(compress, Compress, "w+")

    compression(text_to_convert, dicodicodi, compress);

    fclose(dicodicodi);
    fclose(text_to_convert);
    fclose(compress);
*/
