#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <string.h>

int 	addr_conv(char *address,struct in_addr *inaddr);
int	read_line(int fd,char *buf,int maxlen);
int 	read_all(int fd,void *buf,int n);
int	write_all(int fd,void *buf,int n);
int 	string_split(char *str,int *n,int nlen);
int 	daemon_init();
