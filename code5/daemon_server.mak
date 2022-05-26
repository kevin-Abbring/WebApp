#daemon_server
daemon_server:daemon_server.o comm_func.o
	g++ -o daemon_server daemon_server.o comm_func.o
daemon_server.o:daemon_server.cpp comm_func.h
	g++ -c daemon_server.cpp
comm_func.o:comm_func.cpp comm_func.h
	g++ -c comm_func.cpp
