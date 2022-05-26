#server32
server32: server30.o server302.o
	gcc -o server32 server30.o server302.o
server30.o: server30.c server302.h
	gcc -c server30.c
server302.o: server302.c server302.h
	gcc -c server302.c
