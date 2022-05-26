#ifndef 	_SERVER301_H_
#define 	_SERVER301_H_

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <signal.h>

#define  SERVER_PORT 8081
#define  BACKLOG		5

void serv_response(int sockfd);
int get_the_Data(int nBegin,int nEnd,int* pnData);

#endif


