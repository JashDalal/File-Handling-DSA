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
