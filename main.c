#include <stdio.h>
#include <stdlib.h>

#include "huffman_compression_with_tab.h"
#include "others.h"
#include "unit_tests.h"

int main()
{
    printf("\t--- Projet Huffmam - Version Gui ! ---\n\n");

    FILE* text_to_convert = NULL;
    FILE* compress = NULL;
    FILE* decompress = NULL;

    char path[] = "";
    char compress_path[200];
    char decompress_path[200];

    if (ask_path(path) == 0)
    {
        build_compress_path(path, compress_path);
        build_decompress_path(compress_path, decompress_path);

        compression(text_to_convert, compress, path, compress_path);
        printf("Creation of %s\n", compress_path);
        decompression(compress, decompress, compress_path, decompress_path);
        printf("Creation of %s\n", decompress_path);

        Test_without_non_compress(text_to_convert, compress, decompress, path, compress_path, decompress_path);
  }

    return 0;
}
