#ping.mak
ping:ping.o comm_func.o
	g++ -o ping ping.o comm_func.o
ping.o:ping.cpp comm_func.h
	g++ -c ping.cpp
comm_func.o: comm_func.cpp comm_func.h
	g++ -c comm_func.cpp
