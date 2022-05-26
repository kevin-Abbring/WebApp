#daemon_server
pidtest:pidtest.o comm_func.o
	g++ -o pidtest pidtest.o comm_func.o
pidtest.o:pidtest.cpp comm_func.h
	g++ -c pidtest.cpp
comm_func.o:comm_func.cpp comm_func.h
	g++ -c comm_func.cpp
