#include "Fopen.h"
/*
	   Fread():
       The  function  fread() reads nmemb items of data, each size bytes long,
       from the stream pointed to by stream,  storing  them  at  the  location
       given by ptr.
*/
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

  while((fp->buffcount) && (bytesrd < total)){
    //Byte by Byte replication into temp.
    *temp = *(fp->ptr);
    temp++;fp->ptr++;
    fp->buffcount--;
    bytesrd++;
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
