#include <stdio.h>
typedef struct File {
	int modeflag;
	int fd;
	char buffer[512];
	//We also need a read and write pointer.
}File;
File *Fopen(const char *filename, const char *mode);
size_t Fread(void *ptr, size_t size, size_t nmemb, File *stream);
size_t Fwrite(const void *ptr, size_t size, size_t nmemb,File *stream);
int Fseek(File *stream, long offset, int whence);
long Ftell(File *stream);
int Fgetpos(File *stream, fpos_t *pos);
int Feof(File *stream);
int Fclose(File *stream);
