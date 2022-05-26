#ifndef _SERVER302_H_
#define _SERVER302_H_

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <signal.h>
#define  SERVER_PORT 8082
#define  BACKLOG	5

void serv_response(int sockfd);
int get_the_Avg(int nNum,int* pnData);

#endif
