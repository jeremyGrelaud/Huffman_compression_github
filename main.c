#include <stdio.h>
#include <stdlib.h>

#include "preprocessor_directives_and_structures.h"

#include "Compress/huffman_compression_with_avl_and_fifo.h"
#include "Compress/huffman_compression_with_tab.h"

#include "Conversion/conversion.h"

#include "Unit_Tests/unit_tests.h"

#include "Files/path.h"

int main()
{
    printf("\t--- Projet Huffmam - Final Version! ---\n\n");

    FILE* text_to_convert = NULL;
    FILE* compress = NULL;
    FILE* decompress = NULL;
    FILE* non_compress = NULL;

    char path[] = "";
    
    if (ask_path(path) == 0)
    {
        char compress_path[200];
        char decompress_path[200];
        char non_compress_path[200];
        
        build_non_compress_path(path, non_compress_path);
        printf("\nCreation of %s\n", non_compress_path);
        convert_file_in_binary(text_to_convert, non_compress, path, non_compress_path);

        build_compress_path(path, compress_path);
        printf("\nCreation of %s\n", compress_path);

        //version with avl
        compression_avl(text_to_convert, compress, path, compress_path);

        //version with tab
        //compression(text_to_convert, compress, path, compress_path);

        build_decompress_path(compress_path, decompress_path);
        printf("\nCreation of %s\n", decompress_path);
        decompression(compress, decompress, compress_path, decompress_path);

        Test(text_to_convert, compress, decompress, non_compress, path,compress_path, decompress_path, non_compress_path);
    }

    return 0;
}
