#server31
server31: server30.o server301.o
	gcc -o server31 server30.o server301.o
server30.o: server30.c server301.h
	gcc -c server30.c
server301.o: server301.c server301.h
	gcc -c server301.c
