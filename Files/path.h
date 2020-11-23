#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

int one_letter(FILE* file);
int ask_path(char* path);
void build_compress_path(char* path, char* compress_path);
void build_decompress_path(char* compress_path, char* decompress_path);
void build_non_compress_path(char* path, char* non_compress_path);

#endif // PATH_H_INCLUDED
