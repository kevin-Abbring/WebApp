#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <winsock.h> 
//#include <winsock2.h>
#define MAXDATASIZE 128
#define PORT 3000

int main(int argc,char **argv){
	int sockfd,nbytes;
	char buf[MAXDATASIZE];
	
	//1.��������˵�
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("cant create socket\n");
		exit(1);
	}
	//ָ����������ַ
	struct sockaddr_in srvaddr;
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_port=htons(PORT);
	if(inet_aton("127.0.0.1",srvaddr.sin_addr.s_addr)==-1){
		printf("addr convert error\n");
		exit(1);
	}
	
	//2.���ӷ�����
	if(
		connect(sockfd,//socket������
		(struct sockaddr *)&srvaddr,//��������ַ
		sizeof(struct sockaddr))==-1//��ַ�ṹ����
	)
	//����ֵ:0-yes,-1-no,errno �������
	{
		printf("connect error\n");
		exit(1);
	}
	//3.��������
	sprintf(buf,"hello");
	write(sockfd,buf,strlen(buf));
	//4.������Ӧ
	if((nbytes=read(sockfd,buf,MAXDATASIZE))==-1){
		printf("read error\n");
		exit(1);
	}
	buf[nbytes]='\0';
	printf("srv respons:%s\n",buf);
	//�ر�socket
	close(sockfd);
}
