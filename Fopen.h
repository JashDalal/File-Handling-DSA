#include <stdio.h>

#define READ 1
#define WRITE 2
#define APPEND 3
#define READWRITE 4
#define READAPPEND 5
#define MAX 20
#define MAXBUFF 512
typedef struct File {
	int modeflag;//Mode in which the file is opened
	int fd;//File Descriptor
	int filesize;//Size of the file
	int buffcount;//Number of bytes left to be read from the buffer
	int currcount;//Stores actual size of buffer
	char buffer[MAXBUFF];//Buffer to reduce number of function calls to read(),write().
	char *base;//sets to the base address of the file
	char *ptr;//points to the current location in the file
	int buff_flag;//buffered = 1 or notbuffered = 0
	int rd_n;//Number of times buffer is called and is filled to full capacity
	int rd_rem;//Bytes yet to be read after the buffer is called rd_n times
	int wr_n;//Number of times buffer is called and is filled to full capacity
	int wr_rem;//Bytes yet to be read after the buffer is called wr_n times
	int wr_flag;//Notifies that the writing is complete
	int errflag;//To know whether an error occurs or not
}File;
typedef struct Fpos_t {
	int position;   
	char *ptr;
}Fpos_t;
int fillBuffer(File *fp);
void updateBuffer(File *fp, char *temp);

File *Fopen(const char *filename, const char *mode);
size_t Fread(void *ptr, size_t size, size_t nmemb, File *fp);
size_t Fwrite(void *ptr, size_t size, size_t nmemb,File *stream);
int Fseek(File *stream, long offset, int whence);
long Ftell(File *stream);
int Fgetpos(File *stream, Fpos_t *pos);
int Fsetpos(File *stream, Fpos_t *pos);
int Feof(File *stream);
int Fclose(File *stream);
