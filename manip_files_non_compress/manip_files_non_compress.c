#include <stdio.h>
#include <stdlib.h>
#include <math.h> // for pow function

#include "manip_files_non_compress.h"


void convert_10_to_base_octet(int number, int base, char* numberInBinary)
{
    char* numberInWrongBinary = (char*)malloc(8 * sizeof(char));
    int quotient = 0, reste = 0;

    for(int i=0 ; i<8 ; i++) // conversion from base 10 in base base
    {
        quotient = number / base;
        reste = number % base;
        numberInWrongBinary[i] = reste;
        number = quotient;
    }

    for(int i=0 ; i<8 ; i++){ // reordering -> inversion
        numberInBinary[i] = numberInWrongBinary[8-1-i];
    }

    free(numberInWrongBinary);

}

int convert_octet_to_base_10(char* numberInBinary, int base)
{
    int number = 0;
    for(int i=0 ; i<8 ; i++){
        number += numberInBinary[i] * pow(base, 8-1-i);
    }

    return number;
}

void convert_file_in_binary(FILE* text, FILE* text_in_binary)
{
    int actualCharact = 0;
    do{
        actualCharact = fgetc(text); // we read the character

        if(actualCharact != EOF)
        {
            //AFF(actualCharact, "actualCharact") // print Ascii number of the actual character

            char* charact_convert = (char*)malloc(8 * sizeof(char));
            convert_10_to_base_octet(actualCharact, 2, charact_convert); // conversion in base 2

            for(int i=0 ; i<8 ; i++){
                fprintf(text_in_binary, "%d", charact_convert[i]); // add it in bianry file
            }

            free(charact_convert);
        }

    }while (actualCharact != EOF);

}


void convert_binary_in_file(FILE* text_in_binary, FILE* text_convert)
{
    int compteur = 0, charactAscii = 0, actualCharact = 0;
    char* binary_number = (char*)malloc(8 * sizeof(char));

    do{
        actualCharact = fgetc(text_in_binary); // we read the character -> it is 48 if it is 0 and 49 if it is 1
                                            // fgetc read a character
        if(actualCharact != EOF)
        {
            if(actualCharact == 48){
                binary_number[compteur] = 0;
            }
            else{
                binary_number[compteur] = 1;
            }

            compteur++;

            if(compteur == 8) // after 8 character retrievals, we have 1 byte
            {
                compteur = 0;
                charactAscii = convert_octet_to_base_10(binary_number, 2); // conversion
                fprintf(text_convert, "%c", charactAscii); // add it in decoded file
            }
        }

    }while(actualCharact != EOF);

    free(binary_number);

}
