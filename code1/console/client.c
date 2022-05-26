#include "comm_func.h"
#define 	MAX_RECV_SIZE 4096
#define 	MAX_SEND_SIZE 1024
int main(int argc,char **argv)
{
	int sockfd,nbytes;
	char recv_buf[MAX_RECV_SIZE];
	char send_buf[MAX_SEND_SIZE];
	struct sockaddr_in srvaddr;
	short		port=80;
	char		host[128];
	long int	n1,n2,sum;
		
	switch(argc)
	{
		case 1:
			sprintf(host,"127.0.0.1"); //写入host
			break;
		case 2:
			sprintf(host,"%s",argv[1]);
			break;
		case 3:
			sprintf(host,"%s",argv[1]);
			port=atoi(argv[2]);
			break;
		default:
			printf("argc error\n");
			return 1;
	}

	
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_port=htons(port);	
	printf("addr_conv is doing.\n");
	if(!addr_conv(host,&srvaddr.sin_addr))
	{
		printf("addr convert fail\n");
		return 1;
	}	
	printf("Peer host and port have been got\n");

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		printf("socket error\n");
		exit(1);
	}
	if(connect(sockfd,(struct sockaddr *)&srvaddr,sizeof(struct sockaddr))==-1)
	{
		printf("connect error\n");
		exit(1);
	}
	printf("Connected\n");

	sprintf(send_buf,"hello2");
	printf("Write to peer\n");
	if((nbytes=write_all(sockfd,send_buf,strlen(send_buf)))==-1)
	{
		printf("write error\n");
		exit(1);
	}

	printf("Reading\n");
	if((nbytes=read_all(sockfd,recv_buf,MAX_RECV_SIZE))==-1)
	{
		printf("read error\n");
		exit(1);
	}
	recv_buf[nbytes]='\0';
	printf("read: %s\n",recv_buf);
	close(sockfd);
}
