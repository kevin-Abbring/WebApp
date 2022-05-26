#client
client:client.o comm_func.o
	gcc -o client client.o comm_func.o
client.o:client.c comm_func.h
	gcc -c client.c
comm_func.o:comm_func.c comm_func.h
	gcc -c comm_func.c
