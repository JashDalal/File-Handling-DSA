#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Fopen.h"
int main() {
	File *fp1, *fp2, *fp3;
	char ch[2];
	char arr[20];
	char writ[20] = "Writing in the file";
	size_t bytesread;
	size_t byteswrite;
	fp1 = Fopen("test1.c", "r+");
	fp2 = Fopen("test2.c", "w+");
	fp3 = Fopen("test3.c", "a");

	printf("------Fopen() Testing-----\n");
	printf("----First File----\n");
	printf("File Descriptor:%d\n", fp1->fd);
	printf("File Mode Opened:%d\n", fp1->modeflag);
	printf("----Second File----\n");
	printf("File Descriptor:%d\n", fp2->fd);
	printf("File Mode Opened:%d\n", fp2->modeflag);
	printf("----Third File----\n");
	printf("File Descriptor:%d\n", fp3->fd);
	printf("File Mode Opened:%d\n", fp3->modeflag);
	printf("------Fopen() Testing Completed-----\n");
	printf("\n");
	
	printf("-------Read Function Testing--------\n");
	printf("File Content:\n");
	while(Fread(ch, sizeof(char), 1, fp1))
		printf("%s", ch);
	printf("\n");
	Fseek(fp1, 0, SEEK_SET);
	//lseek(fp1->fd, 0, SEEK_SET);
	fillBuffer(fp1);
	bytesread = Fread(arr, sizeof(char), 10, fp1);
	printf("Number of bytes read are :%ld\n", bytesread);
	printf("Data Read :%s\n", arr);
	printf("-------Read Function Testing Finished--------\n");
	printf("\n");
	
	printf("-------Fwrite() Testing--------\n");
	printf("Contents of the array from which write is done :\n %s\n", writ);
	byteswrite = Fwrite(writ, sizeof(char), 10, fp2);
	printf("Number of bytes written are :%ld\n", byteswrite);
	Fseek(fp2, 0, SEEK_SET);
	//lseek(fp2->fd, 0, SEEK_SET);
	printf("File Contents after writing in it:\n");
	while(Fread(ch, sizeof(char), 1, fp2))
		printf("%s", ch);
	printf("\n");
	printf("-------Fwrite() Testing Finished--------\n");
	printf("\n");
	
	printf("---------Files Closed using Fclose()-------\n");	
	Fclose(fp1);
	Fclose(fp2);
	Fclose(fp3);
	return 0;
}

