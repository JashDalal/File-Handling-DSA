Name : Jash Dalal
MIS : 111707013
Branch and Year: SY I.T.
Project : File I/O.
# File_InputOutput_Library.DSA

Implementing File functions 
	fopen()
	fread()
	fwrite()
	fgetpos()
	feof() 
	ftell()
	fseek() 
	fclose()
	fsetpos()
as done  by the predefined file library functions using the primitive set of functions :open(), close(), read(), write(), etc. 

	FOPEN

	The modes that can be used in fopen are :
	 1."r"  : Read only mode(file must exist) 
	 2."w"  : Write only mode in the filename provided,
	    	  if the file does not exist, then create and write.
	 		 (O_WRONLY | O_CREAT | O_TRUNC)
	 3."a"  : Append mode(append to the end of the file)
	 		 (O_WRONLY | O_CREAT | O_APPEND)
	 4."r+" : Read and write mode(O_RDWR)
	 5."w+" : Creates file and enables read write mode
	 		 (O_RDWR | O_CREAT | O_TRUNC)
	 6."a+" : Creates file and enables read append mode
	 		 (O_RDWR | O_CREAT | O_APPEND)
	 
	 FCLOSE

	  close() returns 0 if the file was 
	  closed properly.
	  It returns -1(EOF) if the file was
	  not closed properly.
	  Here, we also have to free variables
	  and empty buffered arrays which have 
	  malloced in the subsequent function calls.
	 
	 
	 
	FREAD
	The function fread() reads nmemb items of data, 
	each size bytes long, from the stream pointed to by stream,
	storing them at the location given by ptr. 
	
	FWRITE 
	The function fwrite() writes nmemb items of data,
	 each size bytes long, to the stream pointed to by stream, 
	 obtaining them from the location given by ptr.
		 
	FEOF
	
	Returns non-zero values in case when 
	file is not at EOF but
 	if at EOF it returns zero.
 	
 	FSEEK
 	The  fseek() function sets the file position indicator for the stream pointed to by stream.  The new position, measured in bytes, is 		obtained by adding offset bytes to the position specified by whence.  If whence is set to SEEK_SET, SEEK_CUR, or SEEK_END, the offset is 		relative to the start of  the  file,  the
    current  position  indicator,  or  end-of-file, respectively.  A successful call to the fseek() function clears the end-of-file indicator 		for the stream and undoes any effects of the ungetc(3) function on the same stream.

 	FTELL
	The ftell() function obtains the current value of the file position
	indicator for the stream pointed to by stream.
	
	FGETPOS & FSETPOS
	 The fgetpos() and fsetpos() functions are alternate interfaces equivalent to ftell() and fseek() (with whence set to SEEK_SET), setting 		 and storing the current  value of the file offset into or from the object referenced by pos.
