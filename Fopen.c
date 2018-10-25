#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "Fopen.h"

FILE *Fopen(const char *filename, const char *mode) {
	//file->fp = fopen(const char *filename, const char *mode);
	int i = 0, fd;
	/*The modes that can be used in fopen are :
	 *"r"  : Read only mode provided the file exists(O_RDONLY) 
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
	switch(mode[i]) {
	
		case 'r' :
					switch(mode[++i]) {
						case '+' : file->fd = open(filename, O_RDWR);
								   if(file->fd == -1) {
								   		perror("Fopen() failed");
								   		exit(1);
								   }  
								   break;
						case '\0' : file->fd = open(filename, O_RDONLY);
								   	if(file->fd == -1) {
								   		perror("Fopen() failed");
								   		exit(1);
								   	}  
								   	break;
					}
					break;
		case 'w' :
					switch(mode[++i]) {
						case '+' : file->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
								   break;
						case '\0' : file->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
								   	break;
					}
					break;	
					
		case 'a' : 									
					switch(mode[++i]) {
						case '+' : file->fd = open(filename, O_RDWR | O_CREAT | O_APPEND);
								   break;
						case '\0' : file->fd = open(filename, O_WRONLY | O_CREAT | O_APPEND);
								   	break;
					}
					break;
					
		default :	
					
}
