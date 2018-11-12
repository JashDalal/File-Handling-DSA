#include "Fopen.h"
long Ftell(File *fp) {
	long i;
	if(fp->base == NULL) {
		fp->errflag = 1;
		return -1;
	}
	i = fp->currcount;
	return i;
}
