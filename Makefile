try: myLib.o mainF.o Fopen.h
	cc myLib.o mainF.o -Wall -o project
myLib.o: myLib.c Fopen.h
	cc -c myLib.c -Wall
mainF.o: mainF.c Fopen.h
	cc -c mainF.c -Wall

