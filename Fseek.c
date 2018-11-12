#include"File.h"
int Fseek(File *fp, long offset, int whence){  
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
	    
   }
   return 0;
}

