int Fsetpos(File *fp, Fpos_t *pos){
	int x;
	x = fp->ptr - pos->position; 
	fp->currcount +=  x;
	fp->ptr = pos->position;
	return 0;
}
