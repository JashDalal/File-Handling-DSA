#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include "Fopen.h"

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
}
