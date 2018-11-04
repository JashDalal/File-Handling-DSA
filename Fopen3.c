#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "Fopen.h"

#define READ 1
#define WRITE 2
#define APPEND 3
#define READWRITE 4
#define READAPPEND 5
#define MAX 20

/*Global declaration of array of struct Files is necessary
 *for passing multiple files.
 *Maximum number of files that can be opened together is set to "MAX".
 */
 File fp[MAX];
 int i;
File *Fopen(const char *filename, const char *mode) {
	
	/*The modes that can be used in fopen are :
	 *"r"  : Read only mode(file must exist) 
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
		
	if(!(strcmp(mode, "r")) || !(strcmp(mode, "rb"))) {
		(fp[i]).fd = open(filename, O_RDONLY, S_IRUSR);
		(fp[i]).modeflag = READ;
		if((fp[i]).fd == -1) {
			errno = EPERM;
			return NULL;
		}
	}  
	else if(!(strcmp(mode, "r+")) || !(strcmp(mode, "rb+"))) {
	 /*else case is entered in case of
	 * "r+" and "rb+"
	 */
		(fp[i]).fd = open(filename, O_RDWR, S_IRUSR|S_IWUSR);
		(fp[i]).modeflag = READWRITE;
		if((fp[i]).fd == -1) {
			errno = EPERM;
			return NULL;
		}  
	}								 
	else if(!(strcmp(mode, "w")) || !(strcmp(mode, "wb"))) {
		(fp[i]).fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR);
		(fp[i]).modeflag = WRITE;
		if((fp[i]).fd == -1) {
			errno = EPERM;
			return NULL;
		}
	}
	else if(!(strcmp(mode, "w+")) || !(strcmp(mode, "wb+"))) {
	 /*else case is entered in case of
	 * "w+" and "wb+"
	 */
		(fp[i]).fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR|S_IWUSR);
		(fp[i]).modeflag = READWRITE;
		if((fp[i]).fd == -1) {
			errno = EPERM;
			return NULL;
		} 
	}
											   
	else if(!(strcmp(mode, "a")) || !(strcmp(mode, "ab"))) {			
		(fp[i]).fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR);
		(fp[i]).modeflag = APPEND;
		if((fp[i]).fd == -1) {
			errno = EPERM;
			return NULL;
		}  
	}
	
	else if(!(strcmp(mode, "a+")) || !(strcmp(mode, "ab+"))) {
		 (fp[i]).fd = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRUSR|S_IWUSR);
		 (fp[i]).modeflag = READAPPEND;
		 if((fp[i]).fd == -1) {
		 	errno = EPERM;
			return NULL;
		 }
	}		
	else {		   	
		errno = EINVAL;
		return NULL;
	}			
	return (&(fp[i++]));
}

int Fclose(File *stream) {
	/*close() returns 0 if the file was 
	 *closed properly.
	 *It returns -1(EOF) if the file was
	 *not closed properly.
	 *Here, we also have to free variables
	 *and empty buffered arrays which have 
	 *malloced in the subsequent function calls.
	 */
	 
	 return (close(stream->fd));
}


