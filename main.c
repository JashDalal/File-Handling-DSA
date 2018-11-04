#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Fopen.h"
int main() {
	File *fp1, *fp2, *fp3;
	FILE *FP1, *FP2;
	
	fp1 = Fopen("test1.c", "a");
	fp2 = Fopen("test2.c", "w");
	fp3 = Fopen("test3.c", "w");
	
	/*
	FP1 = fopen("Test1.c", "w");
	FP2 = fopen("Test2.c", "a");
	
	printf("----First File----\n");
	printf("File Descriptor:%d\n", FP1->_fileno);
	printf("----Second File----\n");
	printf("File Descriptor:%d\n", FP2->_fileno);
	*/
	
	printf("----First File----\n");
	printf("File Descriptor:%d\n", fp1->fd);
	printf("File Mode Opened:%d\n", fp1->modeflag);
	printf("----Second File----\n");
	printf("File Descriptor:%d\n", fp2->fd);
	printf("File Mode Opened:%d\n", fp2->modeflag);
	printf("----Third File----\n");
	printf("File Descriptor:%d\n", fp3->fd);
	printf("File Mode Opened:%d\n", fp3->modeflag);
	
	Fclose(fp1);
	Fclose(fp2);
	Fclose(fp3);
	return 0;
}

