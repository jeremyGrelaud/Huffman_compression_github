#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path.h"
#include "../Unit_tests/unit_tests.h"

int one_letter(FILE* file)  // return 1 if there s only one type of char; return 0 else
{
    char fst_letter;
    char letter;
    int alpha = 1;
    fscanf(file,"%c",&fst_letter);
    do {
        alpha = fscanf(file, "%c", &letter);
        if(alpha != -1 && letter != fst_letter)
            return 0;
    }while(alpha != -1);

    return 1;
}

int ask_path(char* path)
{
    int continuer, size;
    do{
        continuer = 0;
        printf("Write the path of your file : \n");
        scanf("%s", path);
        size = strlen(path);

        if(path[size-1] != 't' || path[size-2] != 'x' || path[size-3] != 't' || path[size-4] != '.')
        {
            printf("Error ! You don't have seize a \".txt\" file.\n");
            continuer = 1;
        }
        else
        {
            FILE* test = NULL;
            test = fopen(path, "r");
            if(test == NULL)
            {
                printf("Error ! It seems the path is invalid. Try again ...\n");
                continuer = 1;
            }
            else
            {
                if(number_of_caracters(test) == 0){
                    printf("It seems this file do exists, but is empty. Try again ...\n");
                    continuer = 1;
                }
                else if(one_letter(test) == 1){
                    printf("It seems this file do exists, but only contains one different letter. It can't work. Try again ...\n");
                    continuer = 1;
                }
                fclose(test);
            }
        }
    }while(continuer);

    return continuer;

}

void build_compress_path(char* path, char* compress_path)
{
    int size = strlen(path);
    strcpy(compress_path, path);
    compress_path[size-4] = '\0';
    strcat(compress_path, "_huffcomp.txt");
}

void build_decompress_path(char* compress_path, char* decompress_path)
{
    int size = strlen(compress_path);
    strcpy(decompress_path, compress_path);
    decompress_path[size-13] = '\0';
    strcat(decompress_path, "_decomp.txt");
}

void build_non_compress_path(char* path, char* non_compress_path)
{
    int size = strlen(path);
    strcpy(non_compress_path, path);
    non_compress_path[size-4] = '\0';
    strcat(non_compress_path, "_binary.txt");
}
