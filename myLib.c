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

#define allPermissions S_IRUSR|S_IWUSR|S_IRWXU|S_IXUSR|S_IRWXG| S_IRGRP|S_IWGRP|S_IXGRP| S_IRWXO| S_IROTH|S_IWOTH|S_IXOTH

/*Global declaration of array of struct Files is necessary
 *for passing multiple files.
 *Maximum number of files that can be opened together is set to "MAX".
 */
 File fp[MAX];
 int i;
 int count;
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
		(fp[i]).fd = open(filename, O_RDONLY, allPermissions);
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
		(fp[i]).fd = open(filename, O_RDWR, allPermissions);
		(fp[i]).modeflag = READWRITE;
		if((fp[i]).fd == -1) {
			errno = EPERM;
			return NULL;
		}  
	}								 
	else if(!(strcmp(mode, "w")) || !(strcmp(mode, "wb"))) {
		(fp[i]).fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, allPermissions);
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
		(fp[i]).fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, allPermissions);
		(fp[i]).modeflag = READWRITE;
		if((fp[i]).fd == -1) {
			errno = EPERM;
			return NULL;
		} 
	}
											   
	else if(!(strcmp(mode, "a")) || !(strcmp(mode, "ab"))) {			
		(fp[i]).fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, allPermissions);
		(fp[i]).modeflag = APPEND;
		if((fp[i]).fd == -1) {
			errno = EPERM;
			return NULL;
		}  
	}
	
	else if(!(strcmp(mode, "a+")) || !(strcmp(mode, "ab+"))) {
		 (fp[i]).fd = open(filename, O_RDWR | O_CREAT | O_APPEND, allPermissions);
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

int fillBuffer(File *fp){
    int copybytes;
    if(count <= fp->rd_n)
      copybytes = MAXBUFF;
    else
      copybytes = fp->rd_rem;
    fp->ptr = fp->buffer;
    fp->buffcount = read(fp->fd, fp->buffer, copybytes);
	
	//EOF reached
    if(fp->buffcount == 0)
    	return 1;
    	
	//Error occurs because read() fails.
    if(fp->buffcount < 0){
      fp->errflag = 1;
      fp->buffcount = 0;
      return -1;
    }
    return -1;
}

size_t Fread(void *ptr, size_t size, size_t nmemb, File *fp){
  count = 0;
  size_t total = size * nmemb;
  fp->rd_n = total/MAXBUFF;
  fp->rd_rem = total%MAXBUFF;
  size_t bytesrd = 0;
  char *temp = ptr;
  if(fp->modeflag == 2 || fp->modeflag == 3){
		/*File opened in Write only("w") mode is completely erased when an attempt 
		 *is made to read from it. This is handled by O_TRUNC
		 *File opened in Append only("a") mode is retained when an attempt 
		 *is made to read from it.
		 *Number of bytes returned are zero in both cases.
		 */  
    return 0;
  }

  if(fp->buffcount == 0){
  	  count++;
	  fillBuffer(fp);
  }
  if(fp->buffcount == 0) {
  	//printf("Number of bytes read are :%ld\n", bytesrd);
    return bytesrd;
  }
  fp->base = fp->buffer;
  while((fp->buffcount) && (bytesrd < total)){
    //Byte by Byte replication into temp.
    *temp = *(fp->ptr);
    temp++;fp->ptr++;
    fp->buffcount--;bytesrd++;
    //Alternatively, memcpy() can also be used.
    if(fp->buffcount == 0){
      fillBuffer(fp);
      count++;
    }
    if(fp->buffcount == 0) {
      //printf("Number of bytes read are :%ld", bytesrd);
      return bytesrd;
	}
  }
  *(temp ++) = '\0';
  return bytesrd;
}

void updateBuffer(File *fp, char *temp){
  	int flag, wrbytes;
  	int i;
  	count++;
    if(count <= fp->wr_n) {
      wrbytes = MAXBUFF;
    }
    else {
      for(i = 0; i < MAXBUFF; i++)
      	fp->buffer[i] ='\0';
      wrbytes = fp->wr_rem;
      fp->wr_flag = 1;
    }
    if(fp->ptr != NULL){
      memcpy(fp->buffer, temp, wrbytes);
      flag = write(fp->fd, fp->buffer, wrbytes);
      printf("Buffer : %s\n", fp->buffer);
      if(flag == -1){
        fp->errflag = 1;
        return;
      }
	  if(fp->wr_flag)
	  	return;
    }
    
    else{
      memcpy(fp->buffer, temp, wrbytes);
      flag = write(fp->fd, fp->buffer, wrbytes);
    }
    fp->ptr = fp->buffer;
    fp->buffcount = wrbytes; 

   	return;
}
size_t Fwrite(void *ptr, size_t size, size_t nmemb, File *fp){
  count = 0;
  char *temp = ptr; 
  size_t total = size * nmemb;
  fp->wr_n = total/MAXBUFF;
  fp->wr_rem = total%MAXBUFF;
  size_t bytes_written = 0;
  if(fp->modeflag == 1){
  /* If the file is opened in read mode,
   * and Fwrite is called the function returns
   * with number of bytes written as zero. 
   */
    return 0;
  }
  if(total < MAXBUFF) {
  	bytes_written = write(fp->fd, temp, sizeof(char) * total);
  	fp->currcount += bytes_written;
  	return bytes_written;
  } 
  
  if((fp->buffcount == 0) || (fp->ptr == NULL)){
    updateBuffer(fp, temp);
  }
  //if fp->count is zero after Fillbuf i.e EOF has occured
  if(fp->buffcount == 0)
    return bytes_written;
    
  while((fp->buffcount) && (bytes_written < total)){
    *(fp->ptr) = *temp;
    temp++;fp->ptr++;
    fp->buffcount--;bytes_written++;
    if((fp->buffcount == 0) || (fp->ptr == NULL)){
      updateBuffer(fp, temp);
      count++;
    }
    if(fp->buffcount == 0){
      fp->currcount += bytes_written;
      return bytes_written;
    }     
  }
  
  return bytes_written;
}

int Fgetpos(File *fp, Fpos_t *pos) {
	if(fp->base == NULL){
		fp->errflag = 1;		
		return -1;
	}
	pos->position = fp->ptr - fp->base;
	pos->ptr = fp->ptr;
	return 0;		
}

int Fsetpos(File *fp, Fpos_t *pos){
	int x;
	x = fp->ptr - pos->ptr; 
	fp->currcount +=  x;
	fp->ptr = pos->ptr;
	return 0;
}
  
int Fseek(File *fp, long offset, int whence){  
/*This function returns 0 on success
 *and returns -1 on failure in case of an error.
 *When lseek fails Fseek also fails.
 */
   if(whence == SEEK_SET){
     if(lseek(fp->fd, offset, SEEK_SET) != -1){
       fp->ptr = NULL;
       fp->buffcount = 0;
       return 0;
     }
     else{
       fp->errflag = 1;
       return -1;
     }
   }

   if(whence == SEEK_END){
     if(lseek(fp->fd, offset, SEEK_END) != -1){
       fp->ptr = NULL;
       fp->buffcount = 0;
       return 0;
     }
     else{
       fp->errflag = 1;
       return -1;
     }
   }

   if(whence == SEEK_CUR){
      if(lseek(fp->fd, offset - fp->buffcount, 1) != -1){
        fp->ptr = NULL;
        fp->buffcount = 0;
        return 0;
      }
      else{
        fp->errflag = 1;
        return -1;
      }
	}  
	    
  return 0;
}
long Ftell(File *fp) {
	long i;
	if(fp->base == NULL) {
		fp->errflag = 1;
		return -1;
	}	
	i = fp->currcount;
	return i;
}

int Feof(File *fp) {
/*Returns non-zero values in case when 
 *file is not at EOF but
 *if at EOF it returns zero.
 */
	if(*(fp->ptr) == EOF)
		return 1;
	else 
		return 0;
}
	
