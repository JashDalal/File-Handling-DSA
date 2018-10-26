#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "Fopen.h"

#define READ 1
#define WRITE 2
#define APPEND 3
#define READWRITE 4
#define READAPPEND 5

File *Fopen(const char *filename, const char *mode) {
	int i = 0;
	File *fp = malloc(sizeof(File));
	/*The modes that can be used in fopen are :
	 *"w"  : Write only mode in the filename provided,
	 *		 if the file does not exist, then create and write.
	 *		 (O_WRONLY | O_CREAT | O_TRUNC)
	 *"a"  : Append mode(append to the end of the file)
	 		 (O_WRONLY | O_CREAT | O_APPEND)
	 *"r+" : Read and write mode(O_RDWR)
	 *"w+" : Creates file and enables read write mode
	 *		 (O_RDWR | O_CREAT | O_TRUNC)
	 *"a+" : Creates file and enables read append mode		 
	 *		 (O_RDWR | O_CREAT | O_APPEND)
	 */
	 printf("mode[i] is %c\n", mode[i]);
	switch(mode[i]) {
		
		case 'r' :
					
					switch(mode[++i]) {
						case '+' : fp->fd = open(filename, O_RDWR, S_IRUSR|S_IWUSR);
								   fp->modeflag = READWRITE;
								   if(fp->fd == -1) {
								   		errno = EPERM;
								   		return NULL;
								   }  
								   break;
					
						case 'b' :
						case '\0' : 
									fp->fd = open(filename, O_RDONLY, S_IRUSR);
									fp->modeflag = READ;
								   	if(fp->fd == -1) {
								   		errno = EPERM;
								   		return NULL;
								   	}  
								   	break;
					}
					break;
					
		case 'w' :
					switch(mode[++i]) {
						case '+' : fp->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR|S_IWUSR);
								   fp->modeflag = READWRITE;
								   if(fp->fd == -1) {
								   		errno = EPERM;
								   		return NULL;
								   }  
								   break;
					
						case 'b' :
						case '\0' : fp->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR);
									fp->modeflag = WRITE;
								   if(fp->fd == -1) {
								   		errno = EPERM;
								   		return NULL;
								   }  						
								   	break;
					}
					break;	
					
		case 'a' : 									
					switch(mode[++i]) {
						case '+' : fp->fd = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IWUSR);
								   fp->modeflag = READAPPEND;
								   if(fp->fd == -1) {
								   		errno = EPERM;
								   		return NULL;
								   }  						
								   break;
					
						case 'b' :
						case '\0' : fp->fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR);
									fp->modeflag = APPEND;
								   if(fp->fd == -1) {
								   		errno = EPERM;
								   		return NULL;
								   }  
								   	break;				
					}
					break;	
					
		default : errno = EINVAL;
				  return NULL;			
	}
	return fp;
}
