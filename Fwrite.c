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
    if(fp->buffcount == 0)
      return bytes_written;     
  }
  
  return bytes_written;
}

