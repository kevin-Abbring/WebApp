#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>

int 	addr_conv(char *address,struct in_addr *inaddr);
int	read_line(int fd,char *buf,int maxlen);
int 	read_all(int fd,void *buf,int n);
int	write_all(int fd,void *buf,int n);
