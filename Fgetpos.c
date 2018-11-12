int Fgetpos(File *fp, Fpos_t *pos) {
	if(fp->base == NULL){
		fp->errflag = 1;		
		return -1;
	}
	pos->position = fp->ptr - fp->base;
	pos->ptr = fp->ptr;
	return 0;		
}

