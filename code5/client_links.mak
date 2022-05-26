#client_links
client_links: client_links.o comm_func.o
	g++ -o client_links client_links.o comm_func.o
client_links.o: client_links.cpp comm_func.h
	g++ -c client_links.cpp
comm_func.o:comm_func.cpp comm_func.h
	g++ -c comm_func.cpp
