#include <unistd.h>
#include "Fopen.h"
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
